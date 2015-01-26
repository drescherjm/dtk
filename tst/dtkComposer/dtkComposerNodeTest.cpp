/* dtkComposerNodeTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Wed Apr  3 12:16:50 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:51:04 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 577
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
    // Columns of entries
    QTest::addColumn<bool>("a");
    QTest::addColumn<bool>("b");

    // Colums of results
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

void dtkComposerNodeTestCase::testString(void)
{
    dtkComposerNodeString node;
    QVERIFY(node.value().isEmpty());

    QString str = "I'm the king of the World!!";
    node.setValue(str);
    QCOMPARE(str, node.value());
    
    dtkComposerNodeString other;
    QVERIFY(other.receivers().first()->connect(node.emitters().first()));

    node.run();
    other.run();
    QCOMPARE(str, other.value());
}

void dtkComposerNodeTestCase::testStringOperator(void)
{
    //
    QString head = "I'm the king ";
    QString tail = "of the World!!";

    QString sum = head + tail;

    dtkComposerNodeString n_head;
    dtkComposerNodeString n_tail;
    dtkComposerNodeStringOperatorBinaryAppend n_append;
    dtkComposerNodeString n_res;

    QVERIFY(n_append.receivers().first()->connect(n_head.emitters().first()));
    QVERIFY(n_append.receivers().last()->connect( n_tail.emitters().first()));
    QVERIFY(n_res.receivers().first()->connect( n_append.emitters().first()));

    dtkComposerNodeString n_sum;
    dtkComposerNodeStringOperatorBinaryLogicEquality n_equal;
    dtkComposerNodeBoolean n_bool;

    QVERIFY(n_equal.receivers().first()->connect( n_res.emitters().first()));
    QVERIFY(n_equal.receivers().last()->connect(  n_sum.emitters().first()));
    QVERIFY(n_bool.receivers().first()->connect(n_equal.emitters().first()));

    n_head.setValue(head);
    n_tail.setValue(tail);
    n_sum.setValue(sum);

    n_head.run();
    n_tail.run();
    n_sum.run();
    n_append.run();
    n_res.run();
    n_equal.run();
    n_bool.run();

    QCOMPARE(sum, n_res.value());
    QVERIFY(n_bool.value());    
}

void dtkComposerNodeTestCase::testNumber(void)
{
    dtkComposerNodeInteger n_int;
    QVERIFY(n_int.value() == 0);

    dtkComposerNodeReal n_real;
    QVERIFY(n_real.value() == 0);

    qlonglong v_int = 1123581321;
    double v_real = 4 * qAtan(1);

    n_int.setValue(v_int);
    QCOMPARE(v_int, n_int.value());

    n_real.setValue(v_real);
    QCOMPARE(v_real, n_real.value());

    dtkComposerNodeInteger n_ires;
    QVERIFY(n_ires.receivers().first()->connect(n_int.emitters().first()));
    n_int.run();
    n_ires.run();
    QCOMPARE(v_int, n_ires.value());

    dtkComposerNodeReal n_rres;
    QVERIFY(n_rres.receivers().first()->connect(n_real.emitters().first()));

    n_real.run();
    n_rres.run();
    QCOMPARE(v_real, n_rres.value());

    QVERIFY(n_ires.receivers().first()->disconnect(n_int.emitters().first()));
    QVERIFY(n_ires.receivers().first()->connect(n_real.emitters().first()));

    n_real.run();
    n_ires.run();
    QCOMPARE(static_cast<qlonglong>(v_real), n_ires.value());

    QVERIFY(n_rres.receivers().first()->disconnect(n_real.emitters().first()));
    QVERIFY(n_rres.receivers().first()->connect(n_int.emitters().first()));

    n_int.run();
    n_rres.run();
    QCOMPARE(static_cast<double>(v_int), n_rres.value());    
}

void dtkComposerNodeTestCase::testNumberOperatorUnary(void)
{
    double v_r = qAtan(1);

    dtkComposerNodeReal n_r;
    n_r.setValue(v_r);
    n_r.run();

    dtkComposerNodeReal n_end;

    // INCREMENT
    dtkComposerNodeNumberOperatorUnaryIncr n_incr;
    QVERIFY(n_incr.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_incr.emitters().first()));
    n_incr.run();
    n_end.run();
    QCOMPARE((v_r + 1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_incr.emitters().first()));

    // DECREMENT
    dtkComposerNodeNumberOperatorUnaryDecr n_decr;
    QVERIFY(n_decr.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_decr.emitters().first()));
    n_decr.run();
    n_end.run();
    QCOMPARE((v_r - 1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_decr.emitters().first()));

    // SQRT
    dtkComposerNodeNumberOperatorUnarySqrt n_sqrt;
    QVERIFY(n_sqrt.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_sqrt.emitters().first()));
    n_sqrt.run();
    n_end.run();
    QCOMPARE(qSqrt(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_sqrt.emitters().first()));

    // SQUARE
    dtkComposerNodeNumberOperatorUnarySquare n_square;
    QVERIFY(n_square.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_square.emitters().first()));
    n_square.run();
    n_end.run();
    QCOMPARE((v_r * v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_square.emitters().first()));

    // LN
    dtkComposerNodeNumberOperatorUnaryLn n_ln;
    QVERIFY(n_ln.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_ln.emitters().first()));
    n_ln.run();
    n_end.run();
    QCOMPARE(qLn(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_ln.emitters().first()));

    // LOG10
    dtkComposerNodeNumberOperatorUnaryLog10 n_log10;
    QVERIFY(n_log10.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_log10.emitters().first()));
    n_log10.run();
    n_end.run();
    QCOMPARE(qLn(v_r)/qLn(10.), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_log10.emitters().first()));

    // EXP
    dtkComposerNodeNumberOperatorUnaryExp n_exp;
    QVERIFY(n_exp.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_exp.emitters().first()));
    n_exp.run();
    n_end.run();
    QCOMPARE(qExp(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_exp.emitters().first()));

    // COS
    dtkComposerNodeNumberOperatorUnaryCos n_cos;
    QVERIFY(n_cos.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_cos.emitters().first()));
    n_cos.run();
    n_end.run();
    QCOMPARE(qCos(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_cos.emitters().first()));

    // SIN
    dtkComposerNodeNumberOperatorUnarySin n_sin;
    QVERIFY(n_sin.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_sin.emitters().first()));
    n_sin.run();
    n_end.run();
    QCOMPARE(qSin(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_sin.emitters().first()));

    // TAN
    dtkComposerNodeNumberOperatorUnaryTan n_tan;
    QVERIFY(n_tan.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_tan.emitters().first()));
    n_tan.run();
    n_end.run();
    QCOMPARE(qTan(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_tan.emitters().first()));

    // ACOS
    dtkComposerNodeNumberOperatorUnaryAcos n_acos;
    QVERIFY(n_acos.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_acos.emitters().first()));
    n_acos.run();
    n_end.run();
    QCOMPARE(qAcos(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_acos.emitters().first()));

    // ASIN
    dtkComposerNodeNumberOperatorUnaryAsin n_asin;
    QVERIFY(n_asin.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_asin.emitters().first()));
    n_asin.run();
    n_end.run();
    QCOMPARE(qAsin(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_asin.emitters().first()));

    // ATAN
    dtkComposerNodeNumberOperatorUnaryAtan n_atan;
    QVERIFY(n_atan.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_atan.emitters().first()));
    n_atan.run();
    n_end.run();
    QCOMPARE(qAtan(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_atan.emitters().first()));

    // DEG2RAD
    dtkComposerNodeNumberOperatorUnaryDeg2Rad n_d2r;
    QVERIFY(n_d2r.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_d2r.emitters().first()));
    n_d2r.run();
    n_end.run();
    QCOMPARE((v_r * M_PI / 180.), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_d2r.emitters().first()));

    // RAD2DEG
    dtkComposerNodeNumberOperatorUnaryRad2Deg n_r2d;
    QVERIFY(n_r2d.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_r2d.emitters().first()));
    n_r2d.run();
    n_end.run();
    QCOMPARE((v_r / M_PI * 180.), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_r2d.emitters().first()));

    // INVERSE
    dtkComposerNodeNumberOperatorUnaryInv n_inv;
    QVERIFY(n_inv.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_inv.emitters().first()));
    n_inv.run();
    n_end.run();
    QCOMPARE((1. / v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_inv.emitters().first()));

    // OPPOSITE
    dtkComposerNodeNumberOperatorUnaryOpp n_opp;
    QVERIFY(n_opp.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_opp.emitters().first()));
    n_opp.run();
    n_end.run();
    QCOMPARE((-v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_opp.emitters().first()));

    // ABS
    dtkComposerNodeNumberOperatorUnaryAbs n_abs;
    QVERIFY(n_abs.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_abs.emitters().first()));
    n_abs.run();
    n_end.run();
    QCOMPARE(qAbs(v_r), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_abs.emitters().first()));

    dtkComposerNodeInteger n_iend;

    // CEIL
    dtkComposerNodeNumberOperatorUnaryCeil n_ceil;
    QVERIFY(n_ceil.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_iend.receivers().first()->connect(n_ceil.emitters().first()));
    n_ceil.run();
    n_iend.run();
    QCOMPARE(qCeil(v_r), static_cast<int>(n_iend.value()));
    QVERIFY(n_iend.receivers().first()->disconnect(n_ceil.emitters().first()));

    // FLOOR
    dtkComposerNodeNumberOperatorUnaryFloor n_floor;
    QVERIFY(n_floor.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_iend.receivers().first()->connect(n_floor.emitters().first()));
    n_floor.run();
    n_iend.run();
    QCOMPARE(qFloor(v_r), static_cast<int>(n_iend.value()));
    QVERIFY(n_iend.receivers().first()->disconnect(n_floor.emitters().first()));

    // ROUND
    dtkComposerNodeNumberOperatorUnaryRound n_round;
    QVERIFY(n_round.receivers().first()->connect(n_r.emitters().first()));
    QVERIFY(n_iend.receivers().first()->connect(n_round.emitters().first()));
    n_round.run();
    n_iend.run();
    QCOMPARE(qRound(v_r), static_cast<int>(n_iend.value()));
    QVERIFY(n_iend.receivers().first()->disconnect(n_round.emitters().first()));
    
}

void dtkComposerNodeTestCase::testNumberOperatorBinary(void)
{
    qlonglong v_i0 = 112358;
    qlonglong v_i1 = 11235;

    dtkComposerNodeInteger n_i0;
    dtkComposerNodeInteger n_i1;

    n_i0.setValue(v_i0);
    n_i1.setValue(v_i1);
    
    n_i0.run();
    n_i1.run();

    dtkComposerNodeInteger n_iend;

    // EUCLIDIAN DIVISION
    dtkComposerNodeNumberOperatorBinaryEucldiv n_eucl;
    QVERIFY(n_eucl.receivers().first()->connect(n_i0.emitters().first()));
    QVERIFY(n_eucl.receivers().last()->connect( n_i1.emitters().first()));
    QVERIFY(n_iend.receivers().first()->connect(n_eucl.emitters().first()));
    n_eucl.run();
    n_iend.run();
    QCOMPARE((v_i0 / v_i1), n_iend.value());
    QVERIFY(n_iend.receivers().first()->disconnect(n_eucl.emitters().first()));

    // MODULO
    dtkComposerNodeNumberOperatorBinaryModulo n_mod;
    QVERIFY(n_mod.receivers().first()->connect( n_i0.emitters().first()));
    QVERIFY(n_mod.receivers().last()->connect(  n_i1.emitters().first()));
    QVERIFY(n_iend.receivers().first()->connect(n_mod.emitters().first()));
    n_mod.run();
    n_iend.run();
    QCOMPARE((v_i0 % v_i1), n_iend.value());
    QVERIFY(n_iend.receivers().first()->disconnect(n_mod.emitters().first()));

    // ---

    double v_r0 = 4. * qAtan(1.);
    double v_r1 = 10. / 3.;

    dtkComposerNodeReal n_r0;
    dtkComposerNodeReal n_r1;

    n_r0.setValue(v_r0);
    n_r1.setValue(v_r1);
    
    n_r0.run();
    n_r1.run();

    dtkComposerNodeReal n_rend;

    // MIN
    dtkComposerNodeNumberOperatorBinaryMin n_min;
    QVERIFY(n_min.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_min.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_min.emitters().first()));
    n_min.run();
    n_rend.run();
    QCOMPARE(qMin(v_r0, v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_min.emitters().first()));

    // MAX
    dtkComposerNodeNumberOperatorBinaryMax n_max;
    QVERIFY(n_max.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_max.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_max.emitters().first()));
    n_max.run();
    n_rend.run();
    QCOMPARE(qMax(v_r0, v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_max.emitters().first()));

    // MINUS (SUBSTRACTION)
    dtkComposerNodeNumberOperatorBinaryMinus n_minus;
    QVERIFY(n_minus.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_minus.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_minus.emitters().first()));
    n_minus.run();
    n_rend.run();
    QCOMPARE((v_r0 - v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_minus.emitters().first()));

    // PLUS (ADDITION)
    dtkComposerNodeNumberOperatorBinaryPlus n_plus;
    QVERIFY(n_plus.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_plus.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_plus.emitters().first()));
    n_plus.run();
    n_rend.run();
    QCOMPARE((v_r0 + v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_plus.emitters().first()));

    // MULTIPLICATION
    dtkComposerNodeNumberOperatorBinaryMult n_mult;
    QVERIFY(n_mult.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_mult.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_mult.emitters().first()));
    n_mult.run();
    n_rend.run();
    QCOMPARE((v_r0 * v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_mult.emitters().first()));

    // RATIO (DIVISION)
    dtkComposerNodeNumberOperatorBinaryRatio n_ratio;
    QVERIFY(n_ratio.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_ratio.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_ratio.emitters().first()));
    n_ratio.run();
    n_rend.run();
    QCOMPARE((v_r0 / v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_ratio.emitters().first()));

    // Nth ROOT
    dtkComposerNodeNumberOperatorBinaryNthroot n_root;
    QVERIFY(n_root.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_root.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_root.emitters().first()));
    n_root.run();
    n_rend.run();
    QCOMPARE(qPow(v_r0, 1. / v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_root.emitters().first()));

    // POWER
    dtkComposerNodeNumberOperatorBinaryPower n_pow;
    QVERIFY(n_pow.receivers().first()->connect(n_r0.emitters().first()));
    QVERIFY(n_pow.receivers().last()->connect( n_r1.emitters().first()));
    QVERIFY(n_rend.receivers().first()->connect(n_pow.emitters().first()));
    n_pow.run();
    n_rend.run();
    QCOMPARE(qPow(v_r0, v_r1), n_rend.value());
    QVERIFY(n_rend.receivers().first()->disconnect(n_pow.emitters().first()));
}

void dtkComposerNodeTestCase::testNumberComparator(void)
{
    double v_0 = 4. * qAtan(1.);
    double v_1 = 4. * qAtan(1.) + 0.00000000000001 ;

    dtkComposerNodeReal n_0;
    dtkComposerNodeReal n_1;

    n_0.setValue(v_0);
    n_1.setValue(v_1);
    
    n_0.run();
    n_1.run();

    dtkComposerNodeBoolean n_end;

    // EQUAL
    dtkComposerNodeNumberComparatorEqual n_equal;
    QVERIFY(n_equal.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_equal.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_equal.emitters().first()));
    n_equal.run();
    n_end.run();
    QCOMPARE((v_0 == v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_equal.emitters().first()));

    // NOT EQUAL
    dtkComposerNodeNumberComparatorNotequal n_notequal;
    QVERIFY(n_notequal.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_notequal.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_notequal.emitters().first()));
    n_notequal.run();
    n_end.run();
    QCOMPARE((v_0 != v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_notequal.emitters().first()));

    // GREATER THAN
    dtkComposerNodeNumberComparatorGt n_gt;
    QVERIFY(n_gt.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_gt.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_gt.emitters().first()));
    n_gt.run();
    n_end.run();
    QCOMPARE((v_0 > v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_gt.emitters().first()));

    // LESSER THAN
    dtkComposerNodeNumberComparatorLt n_lt;
    QVERIFY(n_lt.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_lt.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_lt.emitters().first()));
    n_lt.run();
    n_end.run();
    QCOMPARE((v_0 < v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_lt.emitters().first()));

    // GREATER THAN OR EQUAL
    dtkComposerNodeNumberComparatorGte n_gte;
    QVERIFY(n_gte.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_gte.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_gte.emitters().first()));
    n_gte.run();
    n_end.run();
    QCOMPARE((v_0 >= v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_gte.emitters().first()));

    // LESSER THAN OR EQUAL
    dtkComposerNodeNumberComparatorLte n_lte;
    QVERIFY(n_lte.receivers().first()->connect(n_0.emitters().first()));
    QVERIFY(n_lte.receivers().last()->connect( n_1.emitters().first()));
    QVERIFY(n_end.receivers().first()->connect(n_lte.emitters().first()));
    n_lte.run();
    n_end.run();
    QCOMPARE((v_0 <= v_1), n_end.value());
    QVERIFY(n_end.receivers().first()->disconnect(n_lte.emitters().first()));
}

void dtkComposerNodeTestCase::cleanupTestCase(void)
{

}

void dtkComposerNodeTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerNodeTest, dtkComposerNodeTestCase)

//#include "dtkComposerNodeTest.moc"
