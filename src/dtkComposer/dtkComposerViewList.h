// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerViewListPrivate;

class DTKCOMPOSER_EXPORT dtkComposerViewList : public QListWidget
{
    Q_OBJECT

public:
     dtkComposerViewList(QWidget *parent = 0);
    ~dtkComposerViewList(void);

public slots:
    void clear(void);

protected slots:
    void update(void);

protected:
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const;
    QStringList mimeTypes(void) const;

private:
    dtkComposerViewListPrivate *d;
};

//
// dtkComposerViewList.h ends here
