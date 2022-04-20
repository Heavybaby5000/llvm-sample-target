set(LLVM_TARGET_DEFINITIONS Sample.td)

tablegen(LLVM SampleGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM SampleGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM SampleGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SampleGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM SampleGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM SampleGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SampleGenMCCodeEmitter.inc -gen-emitter -mc-emitter)
tablegen(LLVM SampleGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SampleGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(SampleCommonTableGen)

add_llvm_target(SampleCodeGen
  SampleAsmPrinter.cpp
  SampleFrameLowering.cpp
  SampleISelDAGtoDAG.cpp
  SampleISelLowering.cpp
  SampleInstrInfo.cpp
  SampleMachineFunction.cpp
  SampleMCInstLower.cpp
  SampleRegisterInfo.cpp
  SampleSelectionDAGInfo.cpp
  SampleSubtarget.cpp
  SampleTargetMachine.cpp
)

add_dependencies(LLVMSampleCodeGen SampleCommonTableGen intrinsics_gen)

add_subdirectory(Disassembler)
add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
