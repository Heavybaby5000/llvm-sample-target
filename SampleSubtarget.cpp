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

SampleSubtarget::SampleSubtarget(const Triple &TT,
                                 const std::string &CPU,
                                 const std::string &FS,
                                 const SampleTargetMachine &TM)
    : SampleGenSubtargetInfo(TT, CPU, FS),
      InstrInfo(*this),
      FrameLowering(*this),
      TLInfo(TM), TSInfo() {
  std::string CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, FS);
}
