For simplicity, the algorithm I will be analyzing in my C program is quicksort. The array being sorted will be size 10 million containing integers without a range (RAND\_MIN to RAND\_MAX). I'm using Ubuntu WSL on a x\_86 architecture.

Since sorting time can flucuate significantly, a sample of ten programs will be conducted for each optimization level, and the average will be recorded. After this simple time comparison is conducted, a more close analysis of the LLVM generated will be done. The analysis of the LLVM will hopefully be easier to interpret than the assembly.
