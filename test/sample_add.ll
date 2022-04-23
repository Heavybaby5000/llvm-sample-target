define i32 @sample_add (i32 %a, i32 %b) nounwind readnone {
entry:
    %add = add nsw i32 %b, %a
    ret i32 %add
}