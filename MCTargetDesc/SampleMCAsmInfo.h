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

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

  class SampleMCAsmInfo : public MCAsmInfoELF {
    void anchor() override {};
  public:
    explicit SampleMCAsmInfo(const Triple &TT);
  };

} // namespace llvm

#endif
