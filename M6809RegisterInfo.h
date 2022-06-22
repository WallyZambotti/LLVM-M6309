//===- M6809RegisterInfo.h - M6809 Register Information Impl ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed Tim Lindner and Boisy Pitre and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the M6809 implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef M6809REGISTERINFO_H
#define M6809REGISTERINFO_H

#include "llvm/Target/MRegisterInfo.h"
#include "M6809GenRegisterInfo.h.inc"

namespace llvm {

class M6809Subtarget;
class TargetInstrInfo;
class Type;

struct M6809RegisterInfo : public M6809GenRegisterInfo {
  M6809Subtarget &Subtarget;
  const TargetInstrInfo &TII;
  
  M6809RegisterInfo(M6809Subtarget &st, const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MBBI,
                           unsigned SrcReg, int FrameIndex,
                           const TargetRegisterClass *RC) const;

  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MBBI,
                            unsigned DestReg, int FrameIndex,
                            const TargetRegisterClass *RC) const;

  void copyRegToReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
                    unsigned DestReg, unsigned SrcReg,
                    const TargetRegisterClass *RC) const;
  
  void reMaterialize(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                     unsigned DestReg, const MachineInstr *Orig) const;

  virtual MachineInstr* foldMemoryOperand(MachineInstr* MI,
                                          unsigned OpNum,
                                          int FrameIndex) const;

  virtual MachineInstr* foldMemoryOperand(MachineInstr* MI,
                                          unsigned OpNum,
                                          MachineInstr* LoadMI) const {
    return 0;
  }

  const unsigned *getCalleeSavedRegs(const MachineFunction *MF = 0) const;

  const TargetRegisterClass* const* getCalleeSavedRegClasses(
                                     const MachineFunction *MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  bool hasFP(const MachineFunction &MF) const;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I) const;

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, RegScavenger *RS = NULL) const;

  void processFunctionBeforeFrameFinalized(MachineFunction &MF) const;

  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;
  
  // Debug information queries.
  unsigned getRARegister() const;
  unsigned getFrameRegister(MachineFunction &MF) const;

  // Exception handling queries.
  unsigned getEHExceptionRegister() const;
  unsigned getEHHandlerRegister() const;
};

} // end namespace llvm

#endif
