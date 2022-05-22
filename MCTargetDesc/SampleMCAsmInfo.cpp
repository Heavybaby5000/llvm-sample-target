//===-- SampleMCAsmInfo.cpp - Sample asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the SampleMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "SampleMCAsmInfo.h"
#include "llvm/ADT/StringRef.h"
using namespace llvm;

SampleMCAsmInfo::SampleMCAsmInfo(const Triple &TT) {
  CodePointerSize = 4;

  PrivateGlobalPrefix = ".L";
  CommentString = ";";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;
}
