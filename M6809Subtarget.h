//=====-- M6809Subtarget.h - Define Subtarget for the M6809 ----*- C++ -*-====//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under the
// University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the M6809 specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#ifndef M6809_SUBTARGET_H
#define M6809_SUBTARGET_H

#include "llvm/Target/TargetSubtarget.h"
#include <string>

namespace llvm {
  class Module;
  
class M6809Subtarget : public TargetSubtarget {
  bool Is6309;
public:
  M6809Subtarget(const Module &M, const std::string &FS);

  bool is6309() const { return Is6309; }
};

} // end namespace llvm

#endif
