//===-- M6809TargetMachine.h - Define TargetMachine for M6809 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the M6809 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef M6809TARGETMACHINE_H
#define M6809TARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameInfo.h"
#include "M6809InstrInfo.h"
#include "M6809Subtarget.h"

namespace llvm {

class Module;

class M6809TargetMachine : public LLVMTargetMachine {
  const TargetData DataLayout;       // Calculates type size & alignment
  M6809Subtarget Subtarget;
  M6809InstrInfo InstrInfo;
  TargetFrameInfo FrameInfo;
  
protected:
  virtual const TargetAsmInfo *createTargetAsmInfo() const;
  
public:
  M6809TargetMachine(const Module &M, const std::string &FS);

  virtual const M6809InstrInfo *getInstrInfo() const { return &InstrInfo; }
  virtual const TargetFrameInfo  *getFrameInfo() const { return &FrameInfo; }
  virtual const TargetSubtarget  *getSubtargetImpl() const{ return &Subtarget; }
  virtual const MRegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }
  virtual const TargetData       *getTargetData() const { return &DataLayout; }
  static unsigned getModuleMatchQuality(const Module &M);

  // Pass Pipeline Configuration
  virtual bool addInstSelector(FunctionPassManager &PM, bool Fast);
  virtual bool addPreEmitPass(FunctionPassManager &PM, bool Fast);
  virtual bool addAssemblyEmitter(FunctionPassManager &PM, bool Fast, 
                                  std::ostream &Out);
};

} // end namespace llvm

#endif
