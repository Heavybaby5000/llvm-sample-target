//===-- SampleMCTargetDesc.h - Sample Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Sample specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef SAMPLEMCTARGETDESC_H
#define SAMPLEMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include "llvm/Support/Debug.h"

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class StringRef;
class Target;
class Triple;
class raw_ostream;
class raw_pwrite_stream;

Target &getTheSampleTarget();

MCCodeEmitter *createSampleMCCodeEmitter(const MCInstrInfo &MCII,
                                         const MCRegisterInfo &MRI,
                                         MCContext &Ctx);

MCAsmBackend *createSampleAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createSampleELFObjectWriter(uint8_t OSABI);
} // End llvm namespace

// Defines symbolic names for Sample registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "SampleGenRegisterInfo.inc"

// Defines symbolic names for the Sample instructions.
#define GET_INSTRINFO_ENUM
#include "SampleGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "SampleGenSubtargetInfo.inc"

#endif
