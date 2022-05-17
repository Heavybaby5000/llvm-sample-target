//===-- SampleRegisterInfo.cpp - Sample Register Information -== --------------===//
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

#define DEBUG_TYPE "sample-reg-info"

#include "SampleRegisterInfo.h"
#include "SampleSubtarget.h"
#include "Sample.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/DebugInfo.h"

#include "MCTargetDesc/SampleMCTargetDesc.h"

#define GET_REGINFO_TARGET_DESC
#include "SampleGenRegisterInfo.inc"

using namespace llvm;

SampleRegisterInfo::
SampleRegisterInfo(const TargetInstrInfo &tii)
  : SampleGenRegisterInfo(Sample::RA), TII(tii) { }

//===----------------------------------------------------------------------===//
// Callee Saved Registers methods
//===----------------------------------------------------------------------===//

// 呼び出し先待避レジスタ
const MCPhysReg* SampleRegisterInfo::
getCalleeSavedRegs(const MachineFunction *MF) const {
    return CSR_SingleFloatOnly_SaveList;
}

// 呼び出し元待避レジスタ
const uint32_t* SampleRegisterInfo::
getCallPreservedMask(const MachineFunction &MF,
                     CallingConv::ID) const {  
    return CSR_SingleFloatOnly_RegMask;
}

BitVector SampleRegisterInfo::
getReservedRegs(const MachineFunction &MF) const {
  static const MCPhysReg ReservedCPURegs[] = {
    Sample::ZERO, Sample::SP, Sample::RA, Sample::V0,
  };

  BitVector Reserved(getNumRegs());
  typedef TargetRegisterClass::iterator RegIter;

  for (unsigned I = 0; I < array_lengthof(ReservedCPURegs); ++I)
    Reserved.set(ReservedCPURegs[I]);

  return Reserved;
}

// FrameIndexをスタックポインタに置き換える
void SampleRegisterInfo::
eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                    unsigned FIOperandNum, RegScavenger *RS) const {
  LLVM_DEBUG(dbgs() << ">> SampleRegisterInfo::eliminateFrameIndex <<\n";);

  MachineInstr &MI = *II;
  const MachineFunction &MF = *MI.getParent()->getParent();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  uint64_t stackSize = MF.getFrameInfo().getStackSize();
  int64_t spOffset = MF.getFrameInfo().getObjectOffset(FrameIndex);
  int64_t Offset = spOffset + stackSize + MI.getOperand(FIOperandNum+1).getImm();
  unsigned FrameReg = Sample::SP;

  LLVM_DEBUG(errs() 
        << "\nFunction : " << MF.getFunction().getName() << "\n"
        << "<--------->\n" << MI
        << "FrameIndex : " << FrameIndex << "\n"
        << "spOffset   : " << spOffset << "\n"
        << "stackSize  : " << stackSize << "\n"
        << "Offset     : " << Offset << "\n" << "<--------->\n");

  LLVM_DEBUG(errs() << "Before:" << MI);
  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false);
  MI.getOperand(FIOperandNum+1).ChangeToImmediate(Offset);
  LLVM_DEBUG(errs() << "After:" << MI);
}

unsigned SampleRegisterInfo::
getFrameRegister(const MachineFunction &MF) const {
    return Sample::SP;
}
