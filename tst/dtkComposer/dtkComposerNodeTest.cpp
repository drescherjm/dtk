/* dtkComposerNodeTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Wed Apr  3 12:16:50 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 14:34:55 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 224
 */

/* Change Log:
 * 
 */

#include "dtkComposerNodeTest.h"

#include <dtkComposer>

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerNodeTestCase::initTestCase(void)
{
    

}

void dtkComposerNodeTestCase::init(void)
{

}

void dtkComposerNodeTestCase::testBoolean(void)
{
    dtkComposerNodeBoolean node;
    QVERIFY(!node.value());

    node.setValue(true);
    QVERIFY(node.value());
    node.run();
    QVERIFY(node.emitters().first()->variant().value<bool>());

    node.setValue(false);
    QVERIFY(!node.value());
    node.run();
    QVERIFY(!node.emitters().first()->variant().value<bool>());
}

void dtkComposerNodeTestCase::testBooleanOperatorUnary(void)
{
    dtkComposerNodeBoolean a;
    dtkComposerNodeBoolean res;

    // NOT

    dtkComposerNodeBooleanOperatorUnaryNot n_not;

    QVERIFY(n_not.receivers().first()->connect(a.emitters().first()));
    QVERIFY(res.receivers().first()->connect(n_not.emitters().first()));

    a.setValue(true);
    a.run();
    n_not.run();
    res.run();
    QCOMPARE(res.value(), (!a.value()));

    a.setValue(false);
    a.run();
    n_not.run();
    res.run();
    QCOMPARE(res.value(), (!a.value()));
}

void dtkComposerNodeTestCase::testBooleanOperatorBinary_data(void)
{
    // Entries of the truth tables
    QTest::addColumn<bool>("a");
    QTest::addColumn<bool>("b");

    // List of operators
    QTest::addColumn<bool>("r_and");
    QTest::addColumn<bool>("r_or");
    QTest::addColumn<bool>("r_xor");
    QTest::addColumn<bool>("r_nand");
    QTest::addColumn<bool>("r_nor");
    QTest::addColumn<bool>("r_xnor");
    QTest::addColumn<bool>("r_imp");
    QTest::addColumn<bool>("r_nimp");

    // Truth tables :        a         b       and      or       xor      nand     nor      xnor     imp      nimp
    QTest::newRow("0 0") << false << false << false << false << false << true  << true  << true  << true  << false ;
    QTest::newRow("1 0") << true  << false << false << true  << true  << true  << false << false << false << true  ;
    QTest::newRow("0 1") << false << true  << false << true  << true  << true  << false << false << true  << false ;
    QTest::newRow("1 1") << true  << true  << true  << true  << false << false << false << true  << true  << false ;
}

void dtkComposerNodeTestCase::testBooleanOperatorBinary(void)
{
    // Retrieves truth tables entries
    QFETCH(bool, a);
    QFETCH(bool, b);
    QFETCH(bool, r_and);
    QFETCH(bool, r_or);
    QFETCH(bool, r_xor);
    QFETCH(bool, r_nand);
    QFETCH(bool, r_nor);
    QFETCH(bool, r_xnor);
    QFETCH(bool, r_imp);
    QFETCH(bool, r_nimp);

    // Input boolean nodes
    dtkComposerNodeBoolean n_a;
    dtkComposerNodeBoolean n_b;

    // Result node
    dtkComposerNodeBoolean n_res;    

    // AND
    dtkComposerNodeBooleanOperatorBinaryAnd n_and;

    QVERIFY(n_and.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_and.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_and.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_and.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_and);

    QVERIFY(n_and.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_and.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_and.emitters().first()));

    // OR
    dtkComposerNodeBooleanOperatorBinaryOr n_or;

    QVERIFY(n_or.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_or.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_or.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_or.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_or);

    QVERIFY(n_or.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_or.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_or.emitters().first()));

    // XOR
    dtkComposerNodeBooleanOperatorBinaryXor n_xor;

    QVERIFY(n_xor.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_xor.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_xor.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_xor.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_xor);

    QVERIFY(n_xor.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_xor.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_xor.emitters().first()));   

    // NAND
    dtkComposerNodeBooleanOperatorBinaryNand n_nand;

    QVERIFY(n_nand.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_nand.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_nand.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_nand.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_nand);

    QVERIFY(n_nand.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_nand.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_nand.emitters().first()));

    // NOR
    dtkComposerNodeBooleanOperatorBinaryNor n_nor;

    QVERIFY(n_nor.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_nor.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_nor.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_nor.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_nor);

    QVERIFY(n_nor.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_nor.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_nor.emitters().first()));

    // XNOR
    dtkComposerNodeBooleanOperatorBinaryXnor n_xnor;

    QVERIFY(n_xnor.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_xnor.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_xnor.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_xnor.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_xnor);

    QVERIFY(n_xnor.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_xnor.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_xnor.emitters().first()));

    // IMP
    dtkComposerNodeBooleanOperatorBinaryImp n_imp;

    QVERIFY(n_imp.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_imp.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_imp.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_imp.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_imp);

    QVERIFY(n_imp.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_imp.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_imp.emitters().first()));

    // NIMP
    dtkComposerNodeBooleanOperatorBinaryNimp n_nimp;

    QVERIFY(n_nimp.receivers().first()->connect(n_a.emitters().first()));
    QVERIFY(n_nimp.receivers().last()->connect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect(n_nimp.emitters().first()));

    n_a.setValue(a);
    n_b.setValue(b);
    n_a.run();
    n_b.run();
    n_nimp.run();
    n_res.run();
    QCOMPARE(n_res.value(), r_nimp);

    QVERIFY(n_nimp.receivers().first()->disconnect(n_a.emitters().first()));
    QVERIFY(n_nimp.receivers().last()->disconnect(n_b.emitters().first()));
    QVERIFY(n_res.receivers().first()->disconnect(n_nimp.emitters().first()));
}

void dtkComposerNodeTestCase::cleanupTestCase(void)
{

}

void dtkComposerNodeTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerNodeTest, dtkComposerNodeTestCase)

//#include "dtkComposerNodeTest.moc"
