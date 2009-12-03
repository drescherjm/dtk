#include "dtkInspectorComposer.h"

class dtkInspectorComposerPrivate
{
public:
};

dtkInspectorComposer::dtkInspectorComposer(QWidget *parent) : QWidget(parent), d(new dtkInspectorComposerPrivate)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

dtkInspectorComposer::~dtkInspectorComposer(void)
{
    delete d;

    d = NULL;
}
