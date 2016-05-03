/* dtkComposerMangager.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/05/02 08:06:42
 */

#include "dtkComposerFactoryManager.h"
#include "dtkComposerNodeFactory.h"

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeConstants.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeDistributed.h"
#include "dtkComposerNodeExec.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeRange.h"
#include "dtkComposerNodeMetaContainer.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeSpawn.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringOperator.h"

#include "dtkComposerNodeLogger.h"
#include "dtkComposerNodePrint.h"


class dtkComposerFactoryManagerPrivate
{
public:
    dtkComposerNodeFactory *factory;

};


dtkComposerFactoryManager::dtkComposerFactoryManager(void) : d(new dtkComposerFactoryManagerPrivate)
{
    d->factory = new dtkComposerNodeFactory;
}

dtkComposerFactoryManager::~dtkComposerFactoryManager(void)
{
    delete d;
}

dtkComposerNodeFactory *dtkComposerFactoryManager::factory(void)
{
    return d->factory;
}

void dtkComposerFactoryManager::initNodeFile(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeFile.json", dtkComposerNodeCreator<dtkComposerNodeFile>);
    d->factory->record(":dtkComposer/dtkComposerNodeFileExists.json", dtkComposerNodeCreator<dtkComposerNodeFileExists>);
    d->factory->record(":dtkComposer/dtkComposerNodeFileList.json", dtkComposerNodeCreator<dtkComposerNodeFileList>);
    d->factory->record(":dtkComposer/dtkComposerNodeFileRead.json", dtkComposerNodeCreator<dtkComposerNodeFileRead>);
    d->factory->record(":dtkComposer/dtkComposerNodeFileWrite.json", dtkComposerNodeCreator<dtkComposerNodeFileWrite>);
    d->factory->record(":dtkComposer/dtkComposerNodeDirectory.json", dtkComposerNodeCreator<dtkComposerNodeDirectory>);
    d->factory->record(":dtkComposer/dtkComposerNodeExec.json", dtkComposerNodeCreator<dtkComposerNodeExec>);
}

void dtkComposerFactoryManager::initNodeBase(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeComposite.json", dtkComposerNodeCreator<dtkComposerNodeComposite>);
    d->factory->record(":dtkComposer/dtkComposerNodeLogger.json",    dtkComposerNodeCreator<dtkComposerNodeLogger>);
    d->factory->record(":dtkComposer/dtkComposerNodePrint.json",     dtkComposerNodeCreator<dtkComposerNodePrint>);
}

void dtkComposerFactoryManager::initNodeDistributed(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeRemote.json",             dtkComposerNodeCreator<dtkComposerNodeRemote>);
    d->factory->record(":dtkComposer/dtkComposerNodeRemoteSubmit.json",       dtkComposerNodeCreator<dtkComposerNodeRemoteSubmit>);
    d->factory->record(":dtkComposer/dtkComposerNodeSpawn.json",              dtkComposerNodeCreator<dtkComposerNodeSpawn>);
    d->factory->record(":dtkComposer/dtkComposerNodeCommunicatorRank.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorRank>);
    d->factory->record(":dtkComposer/dtkComposerNodeCommunicatorSize.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorSize>);
    d->factory->record(":dtkComposer/dtkComposerNodeCommunicatorSend.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorSend>);
    d->factory->record(":dtkComposer/dtkComposerNodeCommunicatorReceive.json",dtkComposerNodeCreator<dtkComposerNodeCommunicatorReceive>);
    d->factory->record(":dtkComposer/dtkComposerNodeAnySource.json",          dtkComposerNodeCreator<dtkComposerNodeAnySource>);
    d->factory->record(":dtkComposer/dtkComposerNodeAnyTag.json",             dtkComposerNodeCreator<dtkComposerNodeAnyTag>);
    d->factory->record(":dtkComposer/dtkComposerNodeControllerRank.json",     dtkComposerNodeCreator<dtkComposerNodeControllerRank>);
}

void dtkComposerFactoryManager::initNodeConstants(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodePi.json", dtkComposerNodeCreator<dtkComposerNodePi>);
    d->factory->record(":dtkComposer/dtkComposerNodeE.json", dtkComposerNodeCreator<dtkComposerNodeE>);
}

void dtkComposerFactoryManager::initNodeBoolean(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeBoolean.json", dtkComposerNodeCreator<dtkComposerNodeBoolean>);

    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorUnaryNot.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorUnaryNot>);

    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryAnd.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryAnd>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryOr.json",   dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryOr>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXor>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNand.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNand>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNor>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXnor.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXnor>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryImp.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryImp>);
    d->factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNimp.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNimp>);
}

void dtkComposerFactoryManager::initNodeControl(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeControlCase.json", dtkComposerNodeCreator<dtkComposerNodeControlCase>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlIf.json",   dtkComposerNodeCreator<dtkComposerNodeControlIf>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlDoWhile.json", dtkComposerNodeCreator<dtkComposerNodeControlDoWhile>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlFor.json",     dtkComposerNodeCreator<dtkComposerNodeControlFor>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlForEach.json", dtkComposerNodeCreator<dtkComposerNodeControlForEach>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlMap.json",     dtkComposerNodeCreator<dtkComposerNodeControlMap>);
    d->factory->record(":dtkComposer/dtkComposerNodeControlWhile.json",   dtkComposerNodeCreator<dtkComposerNodeControlWhile>);
}

void dtkComposerFactoryManager::initNodeNumber(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeInteger.json", dtkComposerNodeCreator<dtkComposerNodeInteger>);
    d->factory->record(":dtkComposer/dtkComposerNodeReal.json", dtkComposerNodeCreator<dtkComposerNodeReal>);
    d->factory->record(":dtkComposer/dtkComposerNodeRange.json", dtkComposerNodeCreator<dtkComposerNodeRange>);

    // -- Unary operators

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAbs.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAbs>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySqrt.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySqrt>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySquare.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySquare>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryInv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryInv>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryIncr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryIncr>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDecr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDecr>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryFloor.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryFloor>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCeil.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCeil>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRound.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRound>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCos.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCos>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySin.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySin>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryTan.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryTan>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAcos.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAcos>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAsin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAsin>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAtan.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAtan>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDeg2Rad.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDeg2Rad>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRad2Deg.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRad2Deg>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLn.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLn>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLog10.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLog10>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryExp.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryExp>);

    // -- Binary operators

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryEucldiv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryEucldiv>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryModulo.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryModulo>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMin>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMax.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMax>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPlus.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPlus>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMinus.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMinus>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMult.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMult>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryRatio.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryRatio>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPower.json",      dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPower>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryNthroot.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryNthroot>);

    // -- Comparator operator

    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorEqual.json",    dtkComposerNodeCreator<dtkComposerNodeNumberComparatorEqual>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorNotequal.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorNotequal>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorGt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGt>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorLt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLt>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorGte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGte>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberComparatorLte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLte>);

    d->factory->record(":dtkComposer/dtkComposerNodeNumberAlmosteq.json",    dtkComposerNodeCreator<dtkComposerNodeNumberAlmosteq>);
    d->factory->record(":dtkComposer/dtkComposerNodeNumberNotalmosteq.json", dtkComposerNodeCreator<dtkComposerNodeNumberNotalmosteq>);
}

void dtkComposerFactoryManager::initNodeString(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeString.json", dtkComposerNodeCreator<dtkComposerNodeString>);
    d->factory->record(":dtkComposer/dtkComposerNodeStringReplace.json", dtkComposerNodeCreator<dtkComposerNodeStringReplace>);
    d->factory->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryAppend.json",   dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryAppend>);
    d->factory->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryLogicEquality.json", dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryLogicEquality>);
}

void dtkComposerFactoryManager::initNodeContainer(void)
{
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainer.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainer>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerAppend.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerAppend>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerAt>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerInsert.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerInsert>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerPrepend.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerPrepend>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerRemoveAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerRemoveAt>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerResize.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerResize>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerSetAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerSetAt>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerSize.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerSize>);
    d->factory->record(":dtkComposer/dtkComposerNodeMetaContainerTakeAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerTakeAt>);
}
