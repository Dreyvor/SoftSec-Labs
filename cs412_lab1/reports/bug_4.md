### Name
Type confusion

### Description
Comparison between unsigned and the value returned by a round (It can overflow while used with big numbers).
It could terminate the program with a SEGV.

### Affected Lines
`resize.c:58-59`

### Expected vs Observed
Normally the program should works correctly even if the resize factor is really big. However the program returns a SEGV.

### Steps to Reproduce
Run the code with some really big resize factor.

#### Command
```
./resize_image poc.png output.png 1000000000000000000000000
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`.

### Suggested Fix Description
Simply replace `y < round(...)` by `y < new_heigth`
Same idea for x but using `new_width` instead of `new_height`.
