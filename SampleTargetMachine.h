//===-- Sample.h - Top-level interface for Sample representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Sample back-end.
//
//===----------------------------------------------------------------------===//
#ifndef SAMPLE_TARGETMACHINE_H
#define SAMPLE_TARGETMACHINE_H

#include "SampleSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Support/Debug.h"

namespace llvm {

class Module;

class SampleTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  SampleSubtarget Subtarget;

 public:
  SampleTargetMachine(const Target &T, const Triple &TT,
                      StringRef CPU, StringRef FS, const TargetOptions &Options,
                      Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                      CodeGenOpt::Level OL, bool JIT);

  const SampleSubtarget *getSubtargetImpl() const {
    return &Subtarget;
  }
  const SampleSubtarget *getSubtargetImpl(const Function &F) const override {
    return getSubtargetImpl();
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // end namespace llvm

#endif
