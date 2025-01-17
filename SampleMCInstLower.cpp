//===-- SampleMCInstLower.cpp - Convert Sample MachineInstr to an MCInst --===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower Sample MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//

#include "SampleMCInstLower.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "sample-mcinst-lower"

using namespace llvm;

MCOperand SampleMCInstLower::
LowerSymbolOperand(const MachineOperand &MO,
                   MachineOperandType MOTy) const {
  LLVM_DEBUG(dbgs() << ">>> LowerSymbolOperand <<<\n");

  switch(MO.getTargetFlags()) {
    default: llvm_unreachable("Invalid target flag!");
    case 0: break;
  }

  const MCSymbol *Symbol;
  unsigned Offset = 0;
  switch (MOTy) {
  case MachineOperand::MO_MachineBasicBlock:
    Symbol = MO.getMBB()->getSymbol();
    break;
  case MachineOperand::MO_GlobalAddress:
    Symbol = Printer.getSymbol(MO.getGlobal());
    Offset = MO.getOffset();
    break;
  case MachineOperand::MO_BlockAddress:
    Symbol = Printer.GetBlockAddressSymbol(MO.getBlockAddress());
    break;
  case MachineOperand::MO_ExternalSymbol:
    Symbol = Printer.GetExternalSymbolSymbol(MO.getSymbolName());
    break;
  case MachineOperand::MO_JumpTableIndex:
    Symbol = Printer.GetJTISymbol(MO.getIndex());
    break;
  case MachineOperand::MO_ConstantPoolIndex:
    Symbol = Printer.GetCPISymbol(MO.getIndex());
    Offset = MO.getOffset();
    break;
  default:
    llvm_unreachable("<unknown operand type>");
  }

  const MCExpr *Expr = MCSymbolRefExpr::create(Symbol, Ctx);

  if (Offset) {
    const MCConstantExpr *OffsetExpr =  MCConstantExpr::create(Offset, Ctx);
    Expr = MCBinaryExpr::createAdd(Expr, OffsetExpr, Ctx);
  }

  return MCOperand::createExpr(Expr);
}

MCOperand SampleMCInstLower::
LowerOperand(const MachineOperand& MO) const {
  LLVM_DEBUG(dbgs() 
        << ">>> LowerOperand:" << MO 
        << " type:" << MO.getType() << "\n");

  MachineOperandType MOTy = MO.getType();
  switch (MOTy) {
  case MachineOperand::MO_Register:
    // Ignore all implicit register operands.
    if (MO.isImplicit()) break;
    return MCOperand::createReg(MO.getReg());
  case MachineOperand::MO_Immediate:
    return MCOperand::createImm(MO.getImm());
  case MachineOperand::MO_MachineBasicBlock:
  case MachineOperand::MO_GlobalAddress:
  case MachineOperand::MO_ExternalSymbol:
  case MachineOperand::MO_JumpTableIndex:
  case MachineOperand::MO_ConstantPoolIndex:
  case MachineOperand::MO_BlockAddress:
    return LowerSymbolOperand(MO, MOTy);
  case MachineOperand::MO_RegisterMask:
    break;
  default:
    llvm_unreachable("unknown operand type");
 }

  return MCOperand();
}

void SampleMCInstLower::
Lower(const MachineInstr *MI, MCInst &OutMI) const {
  LLVM_DEBUG(dbgs() << ">> SampleMCInstLower::Lower <<\n");
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    MCOperand MCOp = LowerOperand(MO);

    if (MCOp.isValid())
      OutMI.addOperand(MCOp);
  }
}
