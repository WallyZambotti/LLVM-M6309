//===- M6809InstrInfo.td - Target Description for M6809 Target ------------===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
// This file describes the M6809 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

// Signed immediate value testing these return true/false in dag operand selection

def simm5   : PatLeaf<(imm), [{ return isInt<5>(N->getSExtValue()); }]>;
def simm8   : PatLeaf<(imm), [{ return isInt<8>(N->getSExtValue()); }]>;
def simm16  : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;
def simm32  : PatLeaf<(imm), [{ return isInt<32>(N->getSExtValue()); }]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "M6809InstrFormats.td"

//===----------------------------------------------------------------------===//
// Feature predicates.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction Pattern Stuff
//===----------------------------------------------------------------------===//

