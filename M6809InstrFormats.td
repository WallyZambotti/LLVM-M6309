//===- M6809RegisterInfo.td - M6809 Register defs -----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Boisy Pitre and is distributed under the 
// University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

def i5imm  : Operand<i5>;

//===----------------------------------------------------------------------===//
//  Describe M6809 instructions format
//
//  All the possible M6809 fields are:
//
//  opcode  - operation code.
//  rs      - src reg.
//  rt      - dst reg (on a 2 regs instr) or src reg (on a 3 reg instr).
//  rd      - dst reg, only used on 3 regs instr.
//  shamt   - only used on shift instructions, contains the shift amount.
//  funct   - combined with opcode field give us an operation code.
//
//===----------------------------------------------------------------------===//

// Generic M6809 Format
class M6809Inst<dag outs, dag ins, string asmstr, list<dag> pattern, 
               InstrItinClass itin>: Instruction 
{
  bits<8>  page;

  field bits<8> Inst;

  let Namespace = "M6809";

  bits<5> opcode;

  // Top bit and lower 4 bits are the 'opcode' field
  let Inst{7} = opcode{4};
  let Inst{3-0} = opcode{3-0};
  
  dag OutOperandList = outs;
  dag InOperandList  = ins;

  let AsmString   = asmstr;
  let Pattern     = pattern;
  let Itinerary   = itin;
}

//===----------------------------------------------------------------------===//
// 16bit Immediate Memory Address Operand Type for Extended Direct or Indirect
//===----------------------------------------------------------------------===//

def MEMxd : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops i16imm);
}

//===----------------------------------------------------------------------===//
// 0 Offset + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMx : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// 5bit Offset + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMx5 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops i5imm FullIndexBase);
}

//===----------------------------------------------------------------------===//
// 8bit Offset + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMx8 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops i8imm FullIndexBase);
}

//===----------------------------------------------------------------------===//
// 16bit Offset + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMx16 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops i16imm FullIndexBase);
}

//===----------------------------------------------------------------------===//
// 8bit Register + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxr8 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops IndexOffset8 FullIndexBase);
}

//===----------------------------------------------------------------------===//
// 16bit Register + 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxr16 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops IndexOffset16 FullIndexBase);
}

//===----------------------------------------------------------------------===//
// Post Inc by 1 of 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxi1 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops FullIndexBase);
}

//===----------------------------------------------------------------------===//
// Post Inc by 2 of 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxi2 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// Pre Dec by 1 of 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxd1 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops FullIndexBase);
}

//===----------------------------------------------------------------------===//
// Pre Dec by 2 of 16bit Register Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxd2 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// 0 Offset + 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxn : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// 8 bit Offset + 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxn8 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// 16bit Offset + 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxn16 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// 8bit Register + 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxrn8 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops IndexOffset8 FullIndexBase);
}

//===----------------------------------------------------------------------===//
// 16bit Register + 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxnr16 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops IndexOffset16 FullIndexBase);
}

//===----------------------------------------------------------------------===//
// Post Inc by 2 of 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxni2 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

//===----------------------------------------------------------------------===//
// Pre Dec by 2 of 16bit Register Indirect Memory Address Operand Type for Indexed
//===----------------------------------------------------------------------===//

def MEMxnd2 : Operand<i16> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops SemiIndexBase);
}

// Some instructions

def LDri : M6809Inst <(outs Int32Regs:$dst), (ins Immd:$imd),
                 "ld$dst #$imd",
                 [(set i32:$dst, (load ADDRri:$imd))]>;

// Multiclass for load register from immediate, Direct, 
multiclass F3_12 <string OpcStr, bits<6> Op3Val, SDNode OpNode> {
  def rr  : F3_1 <2, Op3Val,
                 (outs IntRegs:$dst), (ins IntRegs:$b, IntRegs:$c),
                 !strconcat(OpcStr, " $b, $c, $dst"),
                 [(set i32:$dst, (OpNode i32:$b, i32:$c))]>;
  def ri  : F3_2 <2, Op3Val,
                 (outs IntRegs:$dst), (ins IntRegs:$b, i32imm:$c),
                 !strconcat(OpcStr, " $b, $c, $dst"),
                 [(set i32:$dst, (OpNode i32:$b, simm13:$c))]>;
}

