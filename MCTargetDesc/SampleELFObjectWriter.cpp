//===-- SampleELFObjectWriter.cpp - Sample ELF Writer -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/SampleFixupKinds.h"
#include "MCTargetDesc/SampleMCTargetDesc.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include <list>

using namespace llvm;

namespace {
class SampleELFObjectWriter : public MCELFObjectTargetWriter {
 public:
  SampleELFObjectWriter(uint8_t OSABI);
  ~SampleELFObjectWriter() override;

  // オブジェクトを生成するときやリンク時にアドレス解決するために
  // ELFObjectWriterなどから参照される
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

SampleELFObjectWriter::
SampleELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*_is64Bit*/ false, OSABI, ELF::EM_NONE,
                              /*HasRelocationAddend*/ false) {}

SampleELFObjectWriter::~SampleELFObjectWriter() {}

unsigned SampleELFObjectWriter::
getRelocType(MCContext &Ctx,
             const MCValue &Target,
             const MCFixup &Fixup,
             bool IsPCRel) const {
  // determine the type of the relocation
  unsigned Type = (unsigned)ELF::R_MIPS_NONE;
  unsigned Kind = (unsigned)Fixup.getKind();

  switch (Kind) {
  default:
    llvm_unreachable("invalid fixup kind!");
  case Sample::fixup_Sample_24:
    Type = ELF::R_MIPS_26;
    break;
  }

  return Type;
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createSampleELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<SampleELFObjectWriter>(OSABI);
}
