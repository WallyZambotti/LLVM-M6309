##===- lib/Target/M6809/Makefile ---------------------------*- Makefile -*-===##
# 
#                     The LLVM Compiler Infrastructure
#
# This file was developed by Tim Lindner and Boisy Pitre and is distributed under
# the University of Illinois Open Source License. See LICENSE.TXT for details.
# 
##===----------------------------------------------------------------------===##
LEVEL = ../../..
LIBRARYNAME = LLVMM6809
TARGET = M6809

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = M6809GenRegisterInfo.h.inc \
                M6809GenRegisterNames.inc \
                M6809GenRegisterInfo.inc \
                M6809GenSubtarget.inc

include $(LEVEL)/Makefile.common

