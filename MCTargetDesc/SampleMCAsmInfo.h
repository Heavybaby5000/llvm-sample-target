//===-- SampleMCAsmInfo.h - Sample asm properties --------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the SampleMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef SAMPLE_TARGETASMINFO_H
#define SAMPLE_TARGETASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class StringRef;

  class SampleMCAsmInfo : public MCAsmInfo {
    virtual void anchor() {};
  public:
    explicit SampleMCAsmInfo(StringRef TT);
  };

} // namespace llvm

#endif
