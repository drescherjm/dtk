#ifndef DTKINSPECTORCOMPOSER_H
#define DTKINSPECTORCOMPOSER_H

#include <QtGui>

class dtkInspectorComposerPrivate;

class dtkInspectorComposer : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorComposer(QWidget *parent = 0);
    ~dtkInspectorComposer(void);

private:
    dtkInspectorComposerPrivate *d;
};

#endif // DTKINSPECTORCOMPOSER_H
