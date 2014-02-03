/* @(#)dtkComposerNodeMovieWriter.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/10/11 16:14:07
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeMovieWriter.h"

#include <dtkVideo/dtkVideoEncoder.h>

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkLog/dtkLog.h>

class dtkComposerNodeMovieWriterPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_file;
    dtkComposerTransmitterReceiver<QImage> receiver_frame;
    dtkComposerTransmitterReceiver<qlonglong> receiver_fps;
    dtkComposerTransmitterReceiver<qlonglong> receiver_bitrate;

public:
    dtkVideoEncoder *video;
    qlonglong fps;
    qlonglong bitrate;
};

dtkComposerNodeMovieWriter::dtkComposerNodeMovieWriter(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMovieWriterPrivate)
{
    d->video   = NULL;
    d->bitrate = 3000000;
    d->fps     = 25;
    this->appendReceiver(&(d->receiver_file));
    this->appendReceiver(&(d->receiver_frame));
    this->appendReceiver(&(d->receiver_fps));
    this->appendReceiver(&(d->receiver_bitrate));

}

dtkComposerNodeMovieWriter::~dtkComposerNodeMovieWriter(void)
{
    if (d->video)
        d->video->close();
    delete d;
    d = NULL;
}

QString dtkComposerNodeMovieWriter::type(void)
{
    return "movieWriter";
}

QString dtkComposerNodeMovieWriter::titleHint(void)
{
    return "Movie Writer File";
}

QString dtkComposerNodeMovieWriter::inputLabelHint(int port)
{
    if(port == 0)
        return "file";

    if(port == 1)
        return "frame";

    if(port == 2)
        return "fps";

    if(port == 3)
        return "bitrate";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

void dtkComposerNodeMovieWriter::run(void)
{
    if (!d->receiver_fps.isEmpty()) {
        d->fps = *(d->receiver_fps.data());
    }
    if (!d->receiver_bitrate.isEmpty()) {
        d->bitrate = *(d->receiver_bitrate.data());
    }

    if (!d->receiver_file.isEmpty() && !d->receiver_frame.isEmpty()) {
        QImage *image = d->receiver_frame.data();
        if (!d->video) {
            d->video = new dtkVideoEncoder;
            int gop = 20;
            bool res = d->video->createFile(*(d->receiver_file.data()), image->width(),image->height(),d->bitrate,gop,d->fps);
        }
        d->video->encodeImage(*image);
    }
}


