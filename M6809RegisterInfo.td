//=- M6809RegisterInfo.td - Describe the M6809 Register File ------*- C++ -*-==//
// 
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
// This file describes the M6809 Register file, defining the registers themselves,
// aliases between the registers, and the register classes built out of the
// registers.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Register definitions...
//

let Namespace = "M6809" in {

  // 8-bit registers
  def A  : Register<"A">,  DwarfRegNum<1>;
  def B  : Register<"B">,  DwarfRegNum<2>;
  def E  : Register<"E">,  DwarfRegNum<3>;
  def F  : Register<"F">,  DwarfRegNum<4>;
  def DP : Register<"DP">, DwarfRegNum<5>;
  def MD : Register<"MD">, DwarfRegNum<6>;
  def CC : Register<"CC">, DwarfRegNum<7>;

  // 16-bit registers
  def D  : RegisterWithSubRegs<"D", [A,B]>, DwarfRegNum<8>;
  def W  : RegisterWithSubRegs<"W", [E,F]>, DwarfRegNum<9>;
  def X  : Register<"X">,  DwarfRegNum<10>;
  def Y  : Register<"Y">,  DwarfRegNum<11>;
  def U  : Register<"U">,  DwarfRegNum<12>;
  def S  : Register<"S">,  DwarfRegNum<13>;
  def V  : Register<"V">,  DwarfRegNum<14>;
  def Z  : Register<"Z">,  DwarfRegNum<15>;
  def PC : Register<"PC">, DwarfRegNum<16>;
  
  // 32-bit register
  def Q : RegisterWithSubRegs("Q", [D,W]>, DwarfRegNum<17>;
}

// Register classes.
//
def Int8Regs  : RegisterClass<"M6809", [i8], 8, [A, B, E, F, DP, MD, CC]> {
  let MethodProtos = [{
    iterator allocation_order_end(const MachineFunction &MF) const;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
    Int8RegsClass::allocation_order_end(const MachineFunction &MF) const {
      return end()-3;  // Don't allocate special registers: DP, MD, CC
    }
  }];
}

def Int16Regs : RegisterClass<"M6809", [i16], 8, [D, W, X, Y, U, V, S, PC, Z]> {
  let MethodProtos = [{
    iterator allocation_order_end(const MachineFunction &MF) const;
  }];
  let MethodBodies = [{
    Int16RegsClass::iterator
    Int16RegsClass::allocation_order_end(const MachineFunction &MF) const {
      return end()-4;  // Don't allocate special registers: V, S, PC and Z
    }
  }];
}

def Int32Regs : RegisterClass<"M6809", [i32], 8, [Q]>;

// Base Registers that can accept Index Registers and can pre/post decrement/increment by one or two

def FullIndexBase  : RegisterClass<"M6809", [i8], 8, [U, X, Y]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// Base Registers that do not require Index Registers and can pre/post decrement/increment by two

def SemiIndexBase  : RegisterClass<"M6809", [i8], 8, [W, U, X, Y]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 8 Bit Index Registers that can be used with Base Registers

def IndexOffset8  : RegisterClass<"M6809", [i8], 8, [A, B, E, F]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 Bit Index Registers that can be used with Base Registers

def IndexOffset16  : RegisterClass<"M6809", [i16], 8, [D, W]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 8 bit load store registers

def LoadStore8  : RegisterClass<"M6809", [i8], 8, [A, B, E, F]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 bit load store registers

def LoadStore16  : RegisterClass<"M6809", [i16], 8, [D, W]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 32 bit load store registers

def LoadStore32  : RegisterClass<"M6809", [i32], 8, [Q]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 8 bit full arithmetic registers

def FullArithmetic8  : RegisterClass<"M6809", [i8], 8, [A, B]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 bit arithmetic registers

def FullArithmetic16  : RegisterClass<"M6809", [i16], 8, [D]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 8 bit semi arithmetic registers

def SemiArithmetic8  : RegisterClass<"M6809", [i8], 8, [E, F, A, B]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 bit semi arithmetic registers

def SemiArithmetic16  : RegisterClass<"M6809", [i16], 8, [W, D]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 8 bit iterator registers

def iterator8  : RegisterClass<"M6809", [i8], 8, [E, F, A, B]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 bit iterator registers that affect the condition codes

def iterator16  : RegisterClass<"M6809", [i16], 8, [X, Y, D, W]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}

// 16 bit iterator registers where condition codes are irrelevant

def counter16  : RegisterClass<"M6809", [i16], 8, [U, X, Y, D, W]> {
  let MethodProtos = [{
    iterator;
  }];
  let MethodBodies = [{
    Int8RegsClass::iterator
  }];
}
