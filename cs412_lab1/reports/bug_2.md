# TODO: Fix the src

### Name
Invalid memory access (asking for write access)

### Description
If the user puts a square dimension bigger than the image size (width OR height) the program try to access invalid memory locations (out-of-bound).

### Affected Lines
`checkerboard.c:112-115`

### Expected vs Observed
The program should behave in a way to signal the error and warn the user about his error instead of crashing with a SEGV.

### Steps to Reproduce
Give a square dimension bigger than the image's dimensions.

#### Command
```
./checkerboard poc.png 100 100 110 00dead beaf00
```

#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `checkerboard.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
go to error if the square dimension is bigger than the image's dimension. Add a check at line `checkerboard.c:66`
