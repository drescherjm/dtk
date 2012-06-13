/* dtkVrTrackerKinect_p.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 25 17:16:28 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 17:31:45 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrTrackerKinect_p.h"
#include <dtkVrTrackerKinectConfig.h>

#include <dtkMath/dtkMath.h>
#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <XnHash.h>
#include <XnLog.h>
#include <XnVNite.h>
#include <XnUSB.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define KNCT_CHECK_RC(rc, what)                                 \
    if (rc != XN_STATUS_OK) {                                   \
        printf("%s failed: %s\n", what, xnGetStatusString(rc)); \
    }

#define KNCT_CHECK_ERRORS(rc, errors, what)     \
    if (rc == XN_STATUS_NO_NODE_PRESENT) {	\
        XnChar strError[1024];                  \
        errors.ToString(strError, 1024);	\
        printf("%s\n", strError);               \
    }

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////


class dtkVrTrackerKinectPrivateThread : public QThread
{
public:
    enum SessionState {
        IN_SESSION,
	NOT_IN_SESSION,
        QUICK_REFOCUS
    };

public:
    void run(void);
    void stop(void);

public:
    static void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt);
    static void XN_CALLBACK_TYPE SessionEnding(void* UserCxt);
    static void XN_CALLBACK_TYPE FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt);

    static void XN_CALLBACK_TYPE NewUser(xn::UserGenerator& generator, XnUserID user, void* cookie);
    static void XN_CALLBACK_TYPE LostUser(xn::UserGenerator& generator, XnUserID user, void* cookie);
    static void XN_CALLBACK_TYPE CalibrationStarted(xn::SkeletonCapability& skeleton, XnUserID user, void* cxt);
    static void XN_CALLBACK_TYPE CalibrationEnded(xn::SkeletonCapability& skeleton, XnUserID user, XnBool bSuccess, void* cxt);
    static void XN_CALLBACK_TYPE PoseDetected(xn::PoseDetectionCapability& pose, const XnChar* strPose, XnUserID user, void* cxt);

public:
    bool assignUser(XnUserID user);
    void findUser(void);

public:
    xn::Context context;
    xn::DepthGenerator depth_generator;
    xn::HandsGenerator hands_generator;
    xn::UserGenerator  users_generator;

public:
    XnVSessionManager *session_manager;
    XnVFlowRouter *flow_router;

public:
    SessionState session_state;

public:
    XnUserID user_id;

public:
    bool running;
    bool calibrated;
    
public:
    static dtkVrTrackerKinectPrivateThread *self;

public:
    dtkVrTrackerKinectPrivate *q;

public: // -- head
      dtkVector3D<double> position;
    dtkQuaternion<double> orientation;

public: // -- right hand
      dtkVector3D<double> hand_position;
};

void dtkVrTrackerKinectPrivateThread::run(void)
{
    while(this->running) {
        this->context.WaitAndUpdateAll();
        this->session_manager->Update(&this->context);

        if (this->user_id != 0) {

            // -- head position

            XnSkeletonJointPosition head_position;
            this->users_generator.GetSkeletonCap().GetSkeletonJointPosition(this->user_id, XN_SKEL_HEAD, head_position);
            
            if (head_position.fConfidence > 0.5)
                this->position = dtkVector3D<double>(head_position.position.X, head_position.position.Y, head_position.position.Z);

            // q->emit moved(head_position.position.X/10.0, head_position.position.Y/10.0, head_position.position.Z/10.0 - 100);

            // -- right hand position

            XnSkeletonJointPosition hand_position;
            this->users_generator.GetSkeletonCap().GetSkeletonJointPosition(this->user_id, XN_SKEL_RIGHT_HAND, hand_position);
            
            if (hand_position.fConfidence > 0.5)
                this->hand_position = dtkVector3D<double>(hand_position.position.X, hand_position.position.Y, hand_position.position.Z);

            // -- head orientation

            XnSkeletonJointOrientation head_orientation;
            this->users_generator.GetSkeletonCap().GetSkeletonJointOrientation(this->user_id, XN_SKEL_HEAD, head_orientation);
            
            if (head_orientation.fConfidence > 0.5) {

                dtkMatrixSquared<double> matrix(3);
                matrix[0][0] = head_orientation.orientation.elements[0];
                matrix[0][1] = head_orientation.orientation.elements[3];
                matrix[0][2] = head_orientation.orientation.elements[6];
                matrix[1][0] = head_orientation.orientation.elements[1];
                matrix[1][1] = head_orientation.orientation.elements[4];
                matrix[1][2] = head_orientation.orientation.elements[7];
                matrix[2][0] = head_orientation.orientation.elements[2];
                matrix[2][1] = head_orientation.orientation.elements[5];
                matrix[2][2] = head_orientation.orientation.elements[8];

                this->orientation = dtkQuaternionFromMatSquared<double>(matrix);
            }

            XnPoint3D com;
            this->users_generator.GetCoM(this->user_id, com);
            if (com.Z == 0) {
                this->user_id = 0;
                this->findUser();
            }
        }

        this->usleep(100000);
    }
}

void dtkVrTrackerKinectPrivateThread::stop(void)
{
    this->running = false;
}

// /////////////////////////////////////////////////////////////////

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
    printf("Session start: (%f,%f,%f)\n", ptPosition.X, ptPosition.Y, ptPosition.Z);

    self->session_state = IN_SESSION;
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::SessionEnding(void* UserCxt)
{
    printf("Session end\n");

    self->session_state = NOT_IN_SESSION;
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
    printf("Focus progress: %s @(%f,%f,%f): %f\n", strFocus, ptPosition.X, ptPosition.Y, ptPosition.Z, fProgress);
}

// /////////////////////////////////////////////////////////////////

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::NewUser(xn::UserGenerator& generator, XnUserID user, void* cookie)
{
    if (!self->calibrated)
    {
        printf("Look for pose\n");
        self->users_generator.GetPoseDetectionCap().StartPoseDetection("Psi", user);
        return;
    }
    
    self->assignUser(user);
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::LostUser(xn::UserGenerator& generator, XnUserID user, void* cookie)
{
    printf("Lost user %d\n", user);

    if (self->user_id == user)
    {
        self->user_id = 0;
        self->findUser();
    }
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::CalibrationStarted(xn::SkeletonCapability& skeleton, XnUserID user, void* cxt)
{
    qDebug() << __func__;
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::CalibrationEnded(xn::SkeletonCapability& skeleton, XnUserID user, XnBool bSuccess, void* cxt)
{
    printf("Calibration done [%d] %ssuccessfully\n", user, bSuccess?"":"un");

    if (bSuccess)
    {
        if (!self->calibrated)
        {
            self->users_generator.GetSkeletonCap().SaveCalibrationData(user, 0);
            self->user_id = user;
            self->users_generator.GetSkeletonCap().StartTracking(user);
            self->calibrated = true;
        }
        
        XnUserID aUsers[10];
        XnUInt16 nUsers = 10;

        self->users_generator.GetUsers(aUsers, nUsers);

        for (int i = 0; i < nUsers; ++i)
            self->users_generator.GetPoseDetectionCap().StopPoseDetection(aUsers[i]);
    }
}

void XN_CALLBACK_TYPE dtkVrTrackerKinectPrivateThread::PoseDetected(xn::PoseDetectionCapability& pose, const XnChar* strPose, XnUserID user, void* cxt)
{
    printf("Found pose \"%s\" for user %d\n", strPose, user);

    self->users_generator.GetSkeletonCap().RequestCalibration(user, true);
    self->users_generator.GetPoseDetectionCap().StopPoseDetection(user);
}

// /////////////////////////////////////////////////////////////////

bool dtkVrTrackerKinectPrivateThread::assignUser(XnUserID user)
{
    qDebug() << __func__;

    if (this->user_id)
        return false;
    
    XnPoint3D com; this->users_generator.GetCoM(user, com);

    if (com.Z == 0)
        return false;
    
    printf("Matching for existing calibration\n");

    this->users_generator.GetSkeletonCap().LoadCalibrationData(user, 0);
    this->users_generator.GetSkeletonCap().StartTracking(user);
    this->user_id = user;

    return true;
}

void dtkVrTrackerKinectPrivateThread::findUser(void)
{
    qDebug() << __func__;

    if (this->user_id != 0)
        return;
    
    XnUserID aUsers[20];
    XnUInt16 nUsers = 20;

    this->users_generator.GetUsers(aUsers, nUsers);
    
    for (int i = 0; i < nUsers; ++i)
        if (this->assignUser(aUsers[i]))
            return;
}

// /////////////////////////////////////////////////////////////////

dtkVrTrackerKinectPrivateThread *dtkVrTrackerKinectPrivateThread::self = NULL;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkVrTrackerKinectPrivate::dtkVrTrackerKinectPrivate(void) : QObject(), d(new dtkVrTrackerKinectPrivateThread)
{
    d->flow_router = NULL;
    d->user_id = 0;

    d->running = false;
    d->calibrated = false;

    d->q = this;
    d->self = d;
}

dtkVrTrackerKinectPrivate::~dtkVrTrackerKinectPrivate(void)
{
    delete d;

    d = NULL;
}

void *dtkVrTrackerKinectPrivate::depthGenerator(void)
{
    return &(d->depth_generator);
}

void *dtkVrTrackerKinectPrivate::handsGenerator(void)
{
    return &(d->hands_generator);
}

void *dtkVrTrackerKinectPrivate::usersGenerator(void)
{
    return &(d->users_generator);
}

void dtkVrTrackerKinectPrivate::initialize(void)
{
    XnStatus rc = XN_STATUS_OK;

    xn::EnumerationErrors errors;

    rc = d->context.InitFromXmlFile(DTKVRTRACKERKINECT_XML_PATH, &errors);

    KNCT_CHECK_ERRORS(rc, errors, "InitFromXmlFile");
    KNCT_CHECK_RC(rc, "InitFromXmlFile");

    rc = d->context.FindExistingNode(XN_NODE_TYPE_DEPTH, d->depth_generator);
    
    KNCT_CHECK_RC(rc, "Find depth generator");

    rc = d->context.FindExistingNode(XN_NODE_TYPE_HANDS, d->hands_generator);

    KNCT_CHECK_RC(rc, "Find hands generator");

    rc = d->context.FindExistingNode(XN_NODE_TYPE_USER, d->users_generator);

    KNCT_CHECK_RC(rc, "Find user generator");

    if (!d->users_generator.IsCapabilitySupported(XN_CAPABILITY_SKELETON) ||
        !d->users_generator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
    {
        printf("User generator doesn't support either skeleton or pose detection.\n");
    }

    d->users_generator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

    d->session_manager = new XnVSessionManager;

    rc = d->session_manager->Initialize(&d->context, "Click,Wave", "RaiseHand");

    KNCT_CHECK_RC(rc, "SessionManager::Initialize");

    d->session_manager->RegisterSession(NULL,
                                        dtkVrTrackerKinectPrivateThread::SessionStarting,
                                        dtkVrTrackerKinectPrivateThread::SessionEnding,
                                        dtkVrTrackerKinectPrivateThread::FocusProgress);

    d->flow_router = new XnVFlowRouter;

    d->session_manager->AddListener(d->flow_router);

    rc = d->context.StartGeneratingAll();

    KNCT_CHECK_RC(rc, "StartGenerating");
    
    XnCallbackHandle handle_user_callbacks;
    XnCallbackHandle handle_calibration_callbacks;
    XnCallbackHandle handle_pose_callbacks;
    
    d->users_generator.RegisterUserCallbacks(
        dtkVrTrackerKinectPrivateThread::NewUser,
        dtkVrTrackerKinectPrivateThread::LostUser,
        NULL,
        handle_user_callbacks);

    d->users_generator.GetSkeletonCap().RegisterCalibrationCallbacks(
        dtkVrTrackerKinectPrivateThread::CalibrationStarted,
        dtkVrTrackerKinectPrivateThread::CalibrationEnded,
        NULL,
        handle_calibration_callbacks);

    d->users_generator.GetPoseDetectionCap().RegisterToPoseCallbacks(
        dtkVrTrackerKinectPrivateThread::PoseDetected,
        NULL,
        NULL,
        handle_pose_callbacks);

    d->running = true;
    d->start();
}

void dtkVrTrackerKinectPrivate::uninitialize(void)
{
    d->stop();
}

void dtkVrTrackerKinectPrivate::rotate(int angle)
{
    XN_USB_DEV_HANDLE m_dev;

open:
    const XnUSBConnectionString *paths;
    XnUInt32 count;
    XnStatus res;

    res = xnUSBEnumerateDevices(0x045E /* VendorID */, 0x02B0 /*ProductID*/, &paths, &count);
    if (res != XN_STATUS_OK) {
        xnPrintError(res, "xnUSBEnumerateDevices failed");
    }

    res = xnUSBOpenDeviceByPath(paths[0], &m_dev);
    if (res != XN_STATUS_OK) {
        xnPrintError(res, "xnUSBOpenDeviceByPath failed");
    }

    res = xnUSBSendControl(m_dev, XN_USB_CONTROL_TYPE_VENDOR, 0x06, 0x01, 0x00, NULL,
                           0, 0);
    if (res != XN_STATUS_OK) {
        xnPrintError(res, "xnUSBSendControl 2 failed");
        goto close;
    }
    
rotate:
    res = xnUSBSendControl(m_dev, XN_USB_CONTROL_TYPE_VENDOR, 0x31, angle, 0x00, NULL, 0, 0);
    if (res != XN_STATUS_OK) {
        xnPrintError(res, "xnUSBSendControl failed");
    }

close:
    xnUSBCloseDevice(m_dev);
}

void dtkVrTrackerKinectPrivate::setActive(void *listener)
{
    if (d->flow_router)
        d->flow_router->SetActive(static_cast<XnVMessageListener *>(listener));
}

dtkVector3D<double> dtkVrTrackerKinectPrivate::hand(void)
{
    return d->hand_position;
}

dtkVector3D<double> dtkVrTrackerKinectPrivate::position(void)
{
    return d->position;
}

dtkQuaternion<double> dtkVrTrackerKinectPrivate::orientation(void)
{
    return d->orientation;
}
