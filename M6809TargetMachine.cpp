//===-- M6809TargetMachine.cpp - Define TargetMachine for M6809 -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "M6809TargetAsmInfo.h"
#include "M6809TargetMachine.h"
#include "M6809.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetMachineRegistry.h"
using namespace llvm;

namespace {
  // Register the target.
  RegisterTarget<M6809TargetMachine> X("m6809", "  M6809");
}

const TargetAsmInfo *M6809TargetMachine::createTargetAsmInfo() const {
  return new M6809TargetAsmInfo(*this);
}

/// M6809TargetMachine ctor - Create an ILP32 architecture model
///
M6809TargetMachine::M6809TargetMachine(const Module &M, const std::string &FS)
  : DataLayout("E-p:16:8:8-i16:8:8-f64:8:8"),
    Subtarget(M, FS), InstrInfo(Subtarget),
    FrameInfo(TargetFrameInfo::StackGrowsDown, 8, 0) {
}

unsigned M6809TargetMachine::getModuleMatchQuality(const Module &M) {
  std::string TT = M.getTargetTriple();
  if (TT.size() >= 6 && std::string(TT.begin(), TT.begin()+6) == "m6809-")
    return 20;

  return 0;
}

//bool M6809TargetMachine::addInstSelector(FunctionPassManager &PM, bool Fast) {
//  PM.add(createM6809ISelDag(*this));
//  return false;
//}

/// addPreEmitPass - This pass may be implemented by targets that want to run
/// passes immediately before machine code is emitted.  This should return
/// true if -print-machineinstrs should print out the code after the passes.
//bool M6809TargetMachine::addPreEmitPass(FunctionPassManager &PM, bool Fast) {
//  PM.add(createM6809FPMoverPass(*this));
//  PM.add(createM6809DelaySlotFillerPass(*this));
//  return true;
//}

//bool M6809TargetMachine::addAssemblyEmitter(FunctionPassManager &PM, bool Fast, 
//                                            std::ostream &Out) {
//  // Output assembly language.
//  PM.add(createM6809CodePrinterPass(Out, *this));
//  return false;
//}
