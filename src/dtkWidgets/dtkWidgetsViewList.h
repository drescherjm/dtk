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

#include "dtkWidgetsExport.h"

#include <QtWidgets>

class dtkWidgetsViewListPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsViewList : public QListWidget
{
    Q_OBJECT

public:
     dtkWidgetsViewList(QWidget *parent = 0);
    ~dtkWidgetsViewList(void);

public slots:
    void clear(void);

protected slots:
    void update(void);

protected:
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const;
    QStringList mimeTypes(void) const;

private:
    dtkWidgetsViewListPrivate *d;
};

//
// dtkWidgetsViewList.h ends here
