//===- M6809Subtarget.cpp - M6809 Subtarget Information -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by Tim Lindner and Boisy Pitre and is distributed under the
// University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the M6809 specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "M6809Subtarget.h"
#include "M6809GenSubtarget.inc"
using namespace llvm;

// FIXME: temporary.
#include "llvm/Support/CommandLine.h"
namespace {
  cl::opt<bool> Enable6309("enable-H6809-6309-insts", cl::Hidden,
                          cl::desc("Enable 6309 instructions in the 6809 target"));
}

M6809Subtarget::M6809Subtarget(const Module &M, const std::string &FS) {
  // Set the default features.
  Is6309 = false;
  
  // Determine default and user specified characteristics
  std::string CPU = "generic";

  CPU = "6809";
  
  // Parse features string.
  ParseSubtargetFeatures(FS, CPU);

  // Unless explicitly limited, enable the 6309 instructions.
  if (Enable6309)
    Is6309 = true;
}
