//===-- SampleAsmPrinter.cpp - Sample LLVM assembly writer ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the Sample assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "Sample.h"
#include "SampleInstrInfo.h"
#include "SampleMCInstLower.h"
#include "SampleTargetMachine.h"
#include "MCTargetDesc/SampleInstPrinter.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/IR/Mangler.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

namespace {
class SampleAsmPrinter : public AsmPrinter {
 public:
  SampleAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  StringRef getPassName() const override {
    return "Sample Assembly Printer";
  }

  // should overwrite functions
  void EmitInstruction(const MachineInstr *MI) override;
};
} // end of anonymous namespace

void SampleAsmPrinter::
EmitInstruction(const MachineInstr *MI) {
  LLVM_DEBUG(dbgs() << ">> SampleAsmPinter::EmitInstruction <<\n");
  LLVM_DEBUG(MI->dump());
  SampleMCInstLower MCInstLowering(OutContext, *this);
  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

// Force static initialization.
extern "C" void LLVMInitializeSampleAsmPrinter() {
  RegisterAsmPrinter<SampleAsmPrinter> X(getTheSampleTarget());
}
