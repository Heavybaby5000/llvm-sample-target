//===-- SampleTargetInfo.cpp - Sample Target Implementation -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Sample.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "sample-target-info"

namespace llvm {
Target &getTheSampleTarget() {
  static Target TheSampleTarget;
  return TheSampleTarget;
}
} // namespace llvm

extern "C" void LLVMInitializeSampleTargetInfo() { 
  DEBUG(dbgs() << ">> InitSampleTargetInfo <<\n");
  RegisterTarget<Triple::sample, /*HasJIT=*/false>
    X(getTheSampleTarget(), "sample", "Sample");
}
