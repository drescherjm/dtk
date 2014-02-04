/* numComposerNodePlotCurveFile.cpp --- 
 */

/* Commentary: 
 * 
 */

#include "dtkComposerNodePlotCurveFile.h"

#include dtkComposerTransmitterEmitter.h
#include <dtkComposerTransmitterReceiver.h>

#include <dtkMathSupport/dtkMath.h>

#include <dtkPlot/dtkPlotCurve.h>

#include <dtkLog/dtkLog>

class dtkComposerNodePlotCurveFilePrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_file;

    dtkComposerTransmitterEmitter<dtkPlotCurves> emitter_curves;

public:
    dtkPlotCurves curves;
    QStringList titlesCurve;
    QList<dtkContainerVectorReal> list_vector_x;
    QList<dtkContainerVectorReal> list_vector_y;
};

dtkComposerNodePlotCurveFile::dtkComposerNodePlotCurveFile(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurveFilePrivate)
{
    this->appendReceiver(&(d->receiver_file));

    this->appendEmitter(&(d->emitter_curves));
}

dtkComposerNodePlotCurveFile::~dtkComposerNodePlotCurveFile(void)
{
    if (!d->curves.isEmpty()) {
        foreach (dtkPlotCurve* curve, d->curves) {
            delete curve;
            curve = NULL;
        }
        d->curves.clear();
    }

    delete d;
    d = NULL;
}

QString dtkComposerNodePlotCurveFile::type(void)
{
    return "dtkPlotCurveFile";
}

QString dtkComposerNodePlotCurveFile::titleHint(void)
{
    return "Curve File";
}

QString dtkComposerNodePlotCurveFile::inputLabelHint(int port)
{
    if(port == 0)
        return "file";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodePlotCurveFile::outputLabelHint(int port)
{
    if(port == 0) {
        return "curves list";
    }

    return dtkComposerNodeLeaf::outputLabelHint(port);
}

bool dtkComposerNodePlotCurveFile::read(const QString& fileName)
{
    QString value;

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to read file" << fileName;
        return false;
    }

    QTextStream in(&file);

    dtkContainerVectorReal vx;
    QList<dtkContainerVectorReal> vy;
    QString line;
    QStringList titlesSplit, lineSplit;
    int numberOfCurves;

    int index = 0;

    do {
        line = in.readLine();

        if (index == 0 && line.count() > 0 && line.contains("#")) {
            titlesSplit = line.split(" ", QString::SkipEmptyParts);
            line = in.readLine();
            index++;
        }

        lineSplit = line.split(" ", QString::SkipEmptyParts);

        numberOfCurves = lineSplit.count() - 1;

        if (numberOfCurves<1) {
            qDebug() << "Wrong file format" << fileName;
            return false;
        }

        vx.clear();
        vy.clear();
        for (int i = 0; i<numberOfCurves; i++) {
            vy << dtkContainerVectorReal();
        }

        while (!line.isEmpty()) {
            lineSplit = line.split(" ", QString::SkipEmptyParts);
            vx << lineSplit[0].toDouble();
            for (int i = 0; i<numberOfCurves; i++) {
                vy[i] << lineSplit[i+1].toDouble();
            }
            line = in.readLine();
        }

        for (int i = 0; i<numberOfCurves; i++) {
            d->list_vector_x << vx;
        }
        d->list_vector_y << vy;

        line = in.readLine();
    } while (!line.isNull());

    file.close();

    if ((titlesSplit.count() - 1) == numberOfCurves) {
        for (int i = 0, j = 1; i<numberOfCurves; i++) {
            d->titlesCurve << titlesSplit[j++];
        }
    }

    return true;
}

void dtkComposerNodePlotCurveFile::run(void)
{
    d->titlesCurve.clear();
    d->list_vector_x.clear();
    d->list_vector_y.clear();

    if (d->receiver_file.isEmpty()) {
        dtkWarn() << "no file speficied in Curve File node!";
        return;
    }

    if (!read(*d->receiver_file.data())) {
        return;
    }

    dtkContainerVectorReal vx, vy;
    int numberOfCurves = d->list_vector_x.count();

    if (numberOfCurves == 0) {
        dtkWarn() << "Wrong data found in Curve File node!";
        return;
    }

    int numberOfCurrentCurves = d->curves.count();

    for (int i = numberOfCurves; i<numberOfCurrentCurves; i++) {
        dtkPlotCurve *curve = d->curves.takeLast();
        d->curves.removeLast();
    }

    QVector<QPointF> data;

    int sizex, sizey;

    for (int i = 0; i<numberOfCurves; i++) {
        vx = d->list_vector_x[i];
        vy = d->list_vector_y[i];

        sizex = vx.count();
        sizey = vy.count();

        if (sizex - sizey != 0) {
            dtkWarn() << "size of vectors x and y are different in Curves node (size x = " << sizex << ", size y = " << sizey << ")!";
            return;
        }
    }

    for (int index = 0; index<numberOfCurves; index++) {
        data.clear();

        vx = d->list_vector_x[index];
        vy = d->list_vector_y[index];
        sizex = vx.count();

        for(int i = 0; i<sizex; i++ ) {
            if (dtkIsInfinite(vx[i]) || dtkIsNan(vx[i]) || dtkIsInfinite(vy[i]) || dtkIsNan(vy[i])) {
	        dtkWarn() << "Found wrong values in Curve node";
                continue;
            }
	    data << QPointF(vx[i], vy[i]);
        }

	dtkPlotCurve *curve = NULL;
	if (index < d->curves.count()) {
	  curve = d->curves[index];
          curve->clear();
	} else {
	  curve = new dtkPlotCurve;
	  d->curves << curve;
	}

        if (d->titlesCurve.count() > index) {
            curve->setName(d->titlesCurve[index]);
        }

        curve->setData(data);
    }

    d->emitter_curves.setData(&d->curves);
}

