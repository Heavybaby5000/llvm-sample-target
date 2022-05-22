; RUN: llc -march=sample < %s | FileCheck %s
; RUN: llc -march=sample -debug %s 2>&1 | FileCheck %s -check-prefix=DEBUG

define i32 @sample_add (i32 %a, i32 %b) nounwind readnone {
; CHECK-LABEL: sample_add
; CHECK: .p2align 2
; CHECK:      move $t0, -64
; CHECK-NEXT: add $sp, $sp, $t0
; CHECK-NEXT: store $ra, 60($sp)
; CHECK-NEXT: add $v0, [[REG1:\$a[0-9]+]], [[REG0:\$a[0-9]+]]
; CHECK-NEXT: load $ra, 60($sp)
; CHECK-NEXT: move $t0, 64
; CHECK-NEXT: add $sp, $sp, $t0
; CHECK-NEXT: ret $ra
entry:
    %add = add nsw i32 %b, %a
    ret i32 %add
}

; DEBUG: SampleRegisterInfo::eliminateFrameIndex