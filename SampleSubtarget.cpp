//===-- SampleSubtarget.cpp - Sample Subtarget Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Sample specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "SampleSubtarget.h"
#include "Sample.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "sample-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SampleGenSubtargetInfo.inc"

using namespace llvm;

static std::string computeDataLayout() {
  return "e-p:32:32:32-i8:8:32-i16:16:32-i64:64:64-n32";
}

SampleSubtarget::SampleSubtarget(const std::string &TT,
                                 const std::string &CPU,
                                 const std::string &FS,
                                 const SampleTargetMachine &TM)
    : SampleGenSubtargetInfo(TT, CPU, FS),
      DL(computeDataLayout()),
      InstrInfo(*this),
      FrameLowering(*this),
      TLInfo(TM), TSInfo(&DL) {
  std::string CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, FS);
}
