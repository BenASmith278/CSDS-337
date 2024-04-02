; ModuleID = 'sampleMod'
source_filename = "sampleMod"

define i32 @simple() {
entry:
  ret i32 0
}

define i32 @add(i32 %0, i32 %1) {
entry:
  %2 = add i32 %1, %0
  ret i32 %2
}

define float @addIntFloat(i32 %0, float %1) {
entry:
  %2 = sitofp i32 %0 to float
  %3 = fadd float %2, %1
  ret float %3
}

define i32 @conditional(i1 %0) {
entry:
  %. = select i1 %0, i32 3, i32 5
  %1 = add i32 %., 11
  ret i32 %1
}

define i32 @oneTwoPhi(i1 %0) {
entry:
  %. = select i1 %0, i32 3, i32 5
  %1 = add i32 %., 11
  ret i32 %1
}

define i32 @selection(i1 %0) {
entry:
  %1 = select i1 %0, i32 3, i32 5
  %2 = add i32 %1, 11
  ret i32 %2
}
