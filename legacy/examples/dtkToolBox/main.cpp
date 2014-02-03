/* main.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: mer. oct. 23 13:56:04 2013 (+0200)
 */

/* Change Log:
 * 
 */

#include <dtkGui/dtkToolBox.h>
#include <dtkGui/dtkObjectEditor.h>

#include <QtGui>

class Integer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int n1 READ n1 WRITE setN1 NOTIFY n1Changed)
    Q_PROPERTY(int n2 READ n2 WRITE setN2 NOTIFY n2Changed)

public:
    int n1(void) { return m_n1; }
    int n2(void) { return m_n2; }
    
public slots:
    void setN1(int n) { this->m_n1 = n; emit n1Changed(); }
    void setN2(int n) { this->m_n2 = n; emit n2Changed(); }

signals:
    void n1Changed(void);
    void n2Changed(void);

private:
    int m_n1;
    int m_n2;
};

// ///////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Integer b; b.setObjectName("b"); b.setN1(11); b.setN2(13);
    Integer c; c.setObjectName("c"); c.setN1(121); c.setN2(143);

    //dtkObjectEditor *editor_b = new dtkObjectEditor(&b);
    //dtkObjectEditor *editor_c = new dtkObjectEditor(&c);

    dtkToolBox *box = new dtkToolBox;

    dtkToolBoxItem *item_b = dtkToolBoxItem::fromObject(&b, 0);
    dtkToolBoxItem *item_c = dtkToolBoxItem::fromObject(&c);

    //item_b->setWidget(editor_b, qPrintable(b.objectName()));
    //item_c->setWidget(editor_c, qPrintable(c.objectName()));
    
    //item_b->setExpanded(true);
    //item_c->setEnforced(true);

    box->addItem(item_c);
    box->addItem(item_b);

    box->setOrder(dtkToolBox::AlphaBetics);

    QWidget *widget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(box);

    QMainWindow *window = new QMainWindow;
    window->setCentralWidget(widget);
    window->setUnifiedTitleAndToolBarOnMac(true);
    window->setWindowTitle("Tool Box example");
    window->show();
    window->raise();

    int status = a.exec();

    delete window;

    return status;
}

#include "main.moc"
