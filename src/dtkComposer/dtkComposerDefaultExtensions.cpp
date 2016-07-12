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

#include "dtkComposerDefaultExtensions.h"

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerBaseExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeComposite.json", dtkComposerNodeCreator<dtkComposerNodeComposite>);
    factory->record(":dtkComposer/dtkComposerNodeLogger.json",    dtkComposerNodeCreator<dtkComposerNodeLogger>);
    factory->record(":dtkComposer/dtkComposerNodePrint.json",     dtkComposerNodeCreator<dtkComposerNodePrint>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerFileExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeFile.json", dtkComposerNodeCreator<dtkComposerNodeFile>);
    factory->record(":dtkComposer/dtkComposerNodeFileExists.json", dtkComposerNodeCreator<dtkComposerNodeFileExists>);
    factory->record(":dtkComposer/dtkComposerNodeFileList.json", dtkComposerNodeCreator<dtkComposerNodeFileList>);
    factory->record(":dtkComposer/dtkComposerNodeFileRead.json", dtkComposerNodeCreator<dtkComposerNodeFileRead>);
    factory->record(":dtkComposer/dtkComposerNodeFileWrite.json", dtkComposerNodeCreator<dtkComposerNodeFileWrite>);
    factory->record(":dtkComposer/dtkComposerNodeDirectory.json", dtkComposerNodeCreator<dtkComposerNodeDirectory>);
    factory->record(":dtkComposer/dtkComposerNodeExec.json", dtkComposerNodeCreator<dtkComposerNodeExec>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerDistributedExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeRemote.json",             dtkComposerNodeCreator<dtkComposerNodeRemote>);
    factory->record(":dtkComposer/dtkComposerNodeRemoteSubmit.json",       dtkComposerNodeCreator<dtkComposerNodeRemoteSubmit>);
    factory->record(":dtkComposer/dtkComposerNodeSpawn.json",              dtkComposerNodeCreator<dtkComposerNodeSpawn>);
    factory->record(":dtkComposer/dtkComposerNodeCommunicatorRank.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorRank>);
    factory->record(":dtkComposer/dtkComposerNodeCommunicatorSize.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorSize>);
    factory->record(":dtkComposer/dtkComposerNodeCommunicatorSend.json",   dtkComposerNodeCreator<dtkComposerNodeCommunicatorSend>);
    factory->record(":dtkComposer/dtkComposerNodeCommunicatorReceive.json",dtkComposerNodeCreator<dtkComposerNodeCommunicatorReceive>);
    factory->record(":dtkComposer/dtkComposerNodeAnySource.json",          dtkComposerNodeCreator<dtkComposerNodeAnySource>);
    factory->record(":dtkComposer/dtkComposerNodeAnyTag.json",             dtkComposerNodeCreator<dtkComposerNodeAnyTag>);
    factory->record(":dtkComposer/dtkComposerNodeControllerRank.json",     dtkComposerNodeCreator<dtkComposerNodeControllerRank>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerConstantsExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodePi.json", dtkComposerNodeCreator<dtkComposerNodePi>);
    factory->record(":dtkComposer/dtkComposerNodeE.json", dtkComposerNodeCreator<dtkComposerNodeE>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerControlExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeControlCase.json", dtkComposerNodeCreator<dtkComposerNodeControlCase>);
    factory->record(":dtkComposer/dtkComposerNodeControlIf.json",   dtkComposerNodeCreator<dtkComposerNodeControlIf>);
    factory->record(":dtkComposer/dtkComposerNodeControlDoWhile.json", dtkComposerNodeCreator<dtkComposerNodeControlDoWhile>);
    factory->record(":dtkComposer/dtkComposerNodeControlFor.json",     dtkComposerNodeCreator<dtkComposerNodeControlFor>);
    factory->record(":dtkComposer/dtkComposerNodeControlForEach.json", dtkComposerNodeCreator<dtkComposerNodeControlForEach>);
    factory->record(":dtkComposer/dtkComposerNodeControlMap.json",     dtkComposerNodeCreator<dtkComposerNodeControlMap>);
    factory->record(":dtkComposer/dtkComposerNodeControlWhile.json",   dtkComposerNodeCreator<dtkComposerNodeControlWhile>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerBooleanExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeBoolean.json", dtkComposerNodeCreator<dtkComposerNodeBoolean>);

    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorUnaryNot.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorUnaryNot>);

    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryAnd.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryAnd>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryOr.json",   dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryOr>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXor>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNand.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNand>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNor.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNor>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryXnor.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryXnor>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryImp.json",  dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryImp>);
    factory->record(":dtkComposer/dtkComposerNodeBooleanOperatorBinaryNimp.json", dtkComposerNodeCreator<dtkComposerNodeBooleanOperatorBinaryNimp>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerNumberExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeInteger.json", dtkComposerNodeCreator<dtkComposerNodeInteger>);
    factory->record(":dtkComposer/dtkComposerNodeReal.json", dtkComposerNodeCreator<dtkComposerNodeReal>);
    factory->record(":dtkComposer/dtkComposerNodeRange.json", dtkComposerNodeCreator<dtkComposerNodeRange>);

    // -- Unary operators

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAbs.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAbs>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySqrt.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySqrt>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySquare.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySquare>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryInv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryInv>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryIncr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryIncr>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDecr.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDecr>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryFloor.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryFloor>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCeil.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCeil>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRound.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRound>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryCos.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryCos>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnarySin.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnarySin>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryTan.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryTan>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAcos.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAcos>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAsin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAsin>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryAtan.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryAtan>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryDeg2Rad.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryDeg2Rad>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryRad2Deg.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryRad2Deg>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLn.json",    dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLn>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryLog10.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryLog10>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorUnaryExp.json",   dtkComposerNodeCreator<dtkComposerNodeNumberOperatorUnaryExp>);

    // -- Binary operators

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryEucldiv.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryEucldiv>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryModulo.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryModulo>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMin.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMin>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMax.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMax>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPlus.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPlus>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMinus.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMinus>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryMult.json",  dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryMult>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryRatio.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryRatio>);

    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryPower.json",      dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryPower>);
    factory->record(":dtkComposer/dtkComposerNodeNumberOperatorBinaryNthroot.json", dtkComposerNodeCreator<dtkComposerNodeNumberOperatorBinaryNthroot>);

    // -- Comparator operator

    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorEqual.json",    dtkComposerNodeCreator<dtkComposerNodeNumberComparatorEqual>);
    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorNotequal.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorNotequal>);

    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorGt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGt>);
    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorLt.json",  dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLt>);
    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorGte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorGte>);
    factory->record(":dtkComposer/dtkComposerNodeNumberComparatorLte.json", dtkComposerNodeCreator<dtkComposerNodeNumberComparatorLte>);

    factory->record(":dtkComposer/dtkComposerNodeNumberAlmosteq.json",    dtkComposerNodeCreator<dtkComposerNodeNumberAlmosteq>);
    factory->record(":dtkComposer/dtkComposerNodeNumberNotalmosteq.json", dtkComposerNodeCreator<dtkComposerNodeNumberNotalmosteq>);

}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerStringExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeString.json", dtkComposerNodeCreator<dtkComposerNodeString>);
    factory->record(":dtkComposer/dtkComposerNodeStringReplace.json", dtkComposerNodeCreator<dtkComposerNodeStringReplace>);
    factory->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryAppend.json",   dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryAppend>);
    factory->record(":dtkComposer/dtkComposerNodeStringOperatorBinaryLogicEquality.json", dtkComposerNodeCreator<dtkComposerNodeStringOperatorBinaryLogicEquality>);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerContainerExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposer/dtkComposerNodeMetaContainer.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainer>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerAppend.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerAppend>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerAt>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerInsert.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerInsert>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerPrepend.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerPrepend>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerRemoveAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerRemoveAt>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerResize.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerResize>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerSetAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerSetAt>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerSize.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerSize>);
    factory->record(":dtkComposer/dtkComposerNodeMetaContainerTakeAt.json", dtkComposerNodeCreator<dtkComposerNodeMetaContainerTakeAt>);
}


//
// dtkComposerDefaultExtensions.cpp ends here
