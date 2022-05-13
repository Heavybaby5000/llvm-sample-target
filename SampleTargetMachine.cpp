//===-- SampleTargetMachine.cpp - Define TargetMachine for Sample -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Sample target spec.
//
//===----------------------------------------------------------------------===//

#include "SampleTargetMachine.h"
#include "SampleTargetObjectFile.h"
#include "Sample.h"
#include "llvm/IR/PassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeSampleTarget() {
  // Register the target.
  RegisterTargetMachine<SampleTargetMachine> X(TheSampleTarget);
}

static std::string computeDataLayout() {
  return "e-p:32:32:32-i8:8:32-i16:16:32-i64:64:64-n32";
}

SampleTargetMachine::
SampleTargetMachine(const Target &T, const Triple &TT,
                    StringRef CPU, StringRef FS, const TargetOptions &Options,
                    Reloc::Model RM, CodeModel::Model CM,
                    CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(), TT, CPU, FS, Options, RM, CM, OL),
      TLOF(make_unique<SampleTargetObjectFile>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
/// Sample Code Generator Pass Configuration Options.
class SamplePassConfig : public TargetPassConfig {
 public:
  SamplePassConfig(SampleTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  SampleTargetMachine &getSampleTargetMachine() const {
    return getTM<SampleTargetMachine>();
  }

  virtual bool addInstSelector();
};
} // namespace

TargetPassConfig *SampleTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new SamplePassConfig(this, PM);
}

bool SamplePassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createSampleISelDag(getSampleTargetMachine()));
  return false;
}
