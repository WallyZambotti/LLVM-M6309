//===-- M6809.h - Top-level interface for M6809 representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// M6809 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef TARGET_M6809_H
#define TARGET_M6809_H

#include <iosfwd>
#include <cassert>

namespace llvm {
  class FunctionPass;
  class TargetMachine;

  FunctionPass *createM6809ISelDag(TargetMachine &TM);
  FunctionPass *createM6809CodePrinterPass(std::ostream &OS, TargetMachine &TM);
  FunctionPass *createM6809DelaySlotFillerPass(TargetMachine &TM);
  FunctionPass *createM6809FPMoverPass(TargetMachine &TM);
} // end namespace llvm;

// Defines symbolic names for M6809 registers.  This defines a mapping from
// register name to register number.
//
#include "M6809GenRegisterNames.inc"

// Defines symbolic names for the M6809 instructions.
//
#include "M6809GenInstrNames.inc"


namespace llvm {
  // Enums corresponding to M6809 condition codes, both icc's and fcc's.  These
  // values must be kept in sync with the ones in the .td file.
  namespace M6809CC {
    enum CondCodes {
      ICC_C = 1,  // Carry/Borrow
      ICC_O = 2,  // Overflow
      ICC_Z = 3,  // Zero
      ICC_S = 4,  // Sign
      ICC_H = 5,  // Half Carry
      
      ICC_F = 6,  // FIRQ Disable
      ICC_I = 7,  // IRQ Disbale
      ICC_E = 8,  // Entire
    };
  }
  
  inline static const char *M6809CondCodeToString(M6809CC::CondCodes CC) {
    switch (CC) {
    default: assert(0 && "Unknown condition code");
    case M6809CC::ICC_C: return "c";
    case M6809CC::ICC_O: return "o";
    case M6809CC::ICC_Z: return "z";
    case M6809CC::ICC_S: return "s";
    case M6809CC::ICC_H: return "h";
    case M6809CC::ICC_F: return "f";
    case M6809CC::ICC_I: return "i";
    case M6809CC::ICC_E: return "e";
    }       
  }
}  // end namespace llvm
#endif
