//===-- SampleISelLowering.h - Sample DAG Lowering Interface --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Sample uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef SAMPLE_ISELLOWERING_H
#define SAMPLE_ISELLOWERING_H

#include "Sample.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
namespace SampleISD {
  enum {
    FIRST_NUMBER = ISD::BUILTIN_OP_END,

    // Jump and link (call)
    Call,

    // Return
    Ret
  };
}

class SampleSubtarget;
//===--------------------------------------------------------------------===//
// TargetLowering Implementation
//===--------------------------------------------------------------------===//

class SampleTargetLowering : public TargetLowering {
  const SampleSubtarget &Subtarget;

 public:
  explicit SampleTargetLowering(const SampleTargetMachine &TM);

  /// LowerOperation - Provide custom lowering hooks for some operations.
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  SDValue
  LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                       bool isVarArg,
                       const SmallVectorImpl<ISD::InputArg> &Ins,
                       const SDLoc &dl, SelectionDAG &DAG,
                       SmallVectorImpl<SDValue> &InVals) const override;

  SDValue
  LowerCall(CallLoweringInfo &CLI,
            SmallVectorImpl<SDValue> &InVals) const override;

  virtual SDValue
  LowerCallResult(SDValue Chain, SDValue InFlag,
                  CallingConv::ID CallConv, bool isVarArg,
                  const SmallVectorImpl<ISD::InputArg> &Ins,
                  const SDLoc &dl, SelectionDAG &DAG,
                  SmallVectorImpl<SDValue> &InVals) const;

  SDValue
  LowerReturn(SDValue Chain,
              CallingConv::ID CallConv, bool isVarArg,
              const SmallVectorImpl<ISD::OutputArg> &Outs,
              const SmallVectorImpl<SDValue> &OutVals,
              const SDLoc &dl, SelectionDAG &DAG) const override;

 private:
};
} // end of namespace llvm

#endif // SAMPLE_ISELLOWERING_H
