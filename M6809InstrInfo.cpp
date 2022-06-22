//===- M6809InstrInfo.cpp - M6809 Instruction Information -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the M6809 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "M6809InstrInfo.h"
#include "M6809.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "M6809GenInstrInfo.inc"
using namespace llvm;

M6809InstrInfo::M6809InstrInfo(M6809Subtarget &ST)
  : TargetInstrInfo(M6809Insts, array_lengthof(M6809Insts)),
    RI(ST, *this) {
}

static bool isZeroImm(const MachineOperand &op) {
  return op.isImmediate() && op.getImmedValue() == 0;
}

/// Return true if the instruction is a register to register move and
/// leave the source and dest operands in the passed parameters.
///
bool M6809InstrInfo::isMoveInstr(const MachineInstr &MI,
                                 unsigned &SrcReg, unsigned &DstReg) const {
  assert(0 && "M6809InstrInfo::isMoveInstr: Need to implement");
return false;
}

/// isLoadFromStackSlot - If the specified machine instruction is a direct
/// load from a stack slot, return the virtual or physical register number of
/// the destination along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than loading from the stack slot.
unsigned M6809InstrInfo::isLoadFromStackSlot(MachineInstr *MI,
                                             int &FrameIndex) const {
  assert(0 && "M6809InstrInfo::isLoadFromStackSlot: Need to implement");
  return 0;
}

/// isStoreToStackSlot - If the specified machine instruction is a direct
/// store to a stack slot, return the virtual or physical register number of
/// the source reg along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than storing to the stack slot.
unsigned M6809InstrInfo::isStoreToStackSlot(MachineInstr *MI,
                                            int &FrameIndex) const {
  assert(0 && "M6809InstrInfo::isStoreToStackSlot: Need to implement");
  return 0;
}

unsigned
M6809InstrInfo::InsertBranch(MachineBasicBlock &MBB,MachineBasicBlock *TBB,
                             MachineBasicBlock *FBB,
                             const std::vector<MachineOperand> &Cond)const{
  assert(0 && "M6809InstrInfo::InsertBranch: Need to implement");
  return 1;
}
