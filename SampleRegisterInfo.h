//===-- SampleRegisterInfo.h - Sample Register Information Impl -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Sample implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef SAMPLEREGISTERINFO_H
#define SAMPLEREGISTERINFO_H

#include "Sample.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "SampleGenRegisterInfo.inc"

namespace llvm {
class TargetInstrInfo;
class Type;

struct SampleRegisterInfo : public SampleGenRegisterInfo {
  const TargetInstrInfo &TII;

  SampleRegisterInfo(const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction* MF = 0) const override;
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  /// Stack Frame Processing Methods
  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, unsigned FIOperandNum,
                           RegScavenger *RS = NULL) const override;

  /// Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm


#endif

