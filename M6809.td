//===- M6809.td - Describe the M6809 Target Machine -------------*- C++ -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "../Target.td"

//===----------------------------------------------------------------------===//
// M6809 Subtarget features.
//
 
def FeatureH6309
  : SubtargetFeature<"H6309", "Is6309", "true",
                     "Enable H6309 instructions">;

//===----------------------------------------------------------------------===//
// Register File Description
//===----------------------------------------------------------------------===//

include "M6809RegisterInfo.td"

//===----------------------------------------------------------------------===//
// Instruction Descriptions
//===----------------------------------------------------------------------===//

include "M6809InstrInfo.td"

def M6809InstrInfo : InstrInfo {
  // Define how we want to layout our target-specific information field.
  let TSFlagsFields = [];
  let TSFlagsShifts = [];
}

//===----------------------------------------------------------------------===//
// M6809 processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;
def : Proc<"h6309",           [FeatureH6309]>;


//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def M6809 : Target {
  // Pull in Instruction Info:
  let InstructionSet = M6809InstrInfo;
}
