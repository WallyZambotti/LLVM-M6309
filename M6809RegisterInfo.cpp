//===- M6809RegisterInfo.cpp - M6809 Register Information -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the M6809 implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "M6809.h"
#include "M6809RegisterInfo.h"
#include "M6809Subtarget.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineLocation.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/Type.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
using namespace llvm;

M6809RegisterInfo::M6809RegisterInfo(M6809Subtarget &st,
                                     const TargetInstrInfo &tii)
  : M6809GenRegisterInfo(M6809::ADJCALLSTACKDOWN, M6809::ADJCALLSTACKUP),
    Subtarget(st), TII(tii) {
}

void M6809RegisterInfo::
storeRegToStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                    unsigned SrcReg, int FI,
                    const TargetRegisterClass *RC) const {
  // On the order of operands here: think "[FrameIdx + 0] = SrcReg".
  if (RC == M6809::Int8RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::STr8i)).addFrameIndex(FI).addImm(0)
      .addReg(SrcReg, false, false, true);
  else if (RC == M6809::Int16RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::STr16i)).addFrameIndex(FI).addImm(0)
      .addReg(SrcReg, false, false, true);
  else if (RC == M6809::Int32RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::STr32i)).addFrameIndex(FI).addImm(0)
      .addReg(SrcReg, false, false, true);
  else
    assert(0 && "Can't store this register to stack slot");
}

void M6809RegisterInfo::
loadRegFromStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                     unsigned DestReg, int FI,
                     const TargetRegisterClass *RC) const {
  if (RC == M6809::Int8RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::LDr8i), DestReg).addFrameIndex(FI).addImm(0);
  else if (RC == M6809::Int16RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::LDFr16i), DestReg).addFrameIndex(FI).addImm(0);
  else if (RC == M6809::Int32RegsRegisterClass)
    BuildMI(MBB, I, TII.get(M6809::LDDFr32i), DestReg).addFrameIndex(FI).addImm(0);
  else
    assert(0 && "Can't load this register from stack slot");
}

void M6809RegisterInfo::copyRegToReg(MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I,
                                     unsigned DestReg, unsigned SrcReg,
                                     const TargetRegisterClass *RC) const {
  BuildMI(MBB, I, TII.get(M6809::TFR), DestReg).addReg(SrcReg);
}

void M6809RegisterInfo::reMaterialize(MachineBasicBlock &MBB,
                                      MachineBasicBlock::iterator I,
                                      unsigned DestReg,
                                      const MachineInstr *Orig) const {
  assert(0 && "reMaterialize: this code is unexamined.");
  MachineInstr *MI = Orig->clone();
  MI->getOperand(0).setReg(DestReg);
  MBB.insert(I, MI);
}

MachineInstr *M6809RegisterInfo::foldMemoryOperand(MachineInstr* MI,
                                                   unsigned OpNum,
                                                   int FI) const {
  MachineInstr *NewMI = NULL;

  return NewMI;
}

const unsigned* M6809RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF)
                                                                         const {
  static const unsigned CalleeSavedRegs[] = { 0 };
  return CalleeSavedRegs;
}

BitVector M6809RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  
  /* Always reserve these registers */
  Reserved.set(M6809::CC);
  Reserved.set(M6809::DP);
  Reserved.set(M6809::MD);
  Reserved.set(M6809::S);
  
  if( !Subtarget.is6309() )
  {
  	  /* Reserve these on a 6809 target */
	  Reserved.set(M6809::E);
	  Reserved.set(M6809::F);
	  Reserved.set(M6809::W);
	  Reserved.set(M6809::V);
	  Reserved.set(M6809::Z);
  }

  return Reserved;
}

const TargetRegisterClass* const*
M6809RegisterInfo::getCalleeSavedRegClasses(const MachineFunction *MF) const {
  static const TargetRegisterClass * const CalleeSavedRegClasses[] = { 0 };
  return CalleeSavedRegClasses;
}

bool M6809RegisterInfo::hasFP(const MachineFunction &MF) const {
  return false;
}

void M6809RegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {
  assert(0 && "eliminateCallFramePseudoInstr: We're using Psuedo Instructions?");
}

void M6809RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  assert(0 && "eliminateFrameIndex: Need to implement");
}

void M6809RegisterInfo::
processFunctionBeforeFrameFinalized(MachineFunction &MF) const {}

void M6809RegisterInfo::emitPrologue(MachineFunction &MF) const {
  assert(0 && "emitPrologue: Need to implement");
}

void M6809RegisterInfo::emitEpilogue(MachineFunction &MF,
                                     MachineBasicBlock &MBB) const {
  assert(0 && "emitEpilogue: Need to implement");
}

unsigned M6809RegisterInfo::getRARegister() const {
  assert(0 && "What is the return address register");
  return 0;
}

unsigned M6809RegisterInfo::getFrameRegister(MachineFunction &MF) const {
  assert(0 && "What is the frame register");
  return NULL;
}

unsigned M6809RegisterInfo::getEHExceptionRegister() const {
  assert(0 && "What is the exception register");
  return 0;
}

unsigned M6809RegisterInfo::getEHHandlerRegister() const {
  assert(0 && "What is the exception handler register");
  return 0;
}

#include "M6809GenRegisterInfo.inc"

