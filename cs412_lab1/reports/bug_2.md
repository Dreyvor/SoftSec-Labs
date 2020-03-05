### Name
"Undefined behavior"

### Description
If we put a `square_width` which does not divide the width and the height, there is an error that pops at line `checkerboard.c:122`.
It also prevents the case where we give a `square_width` bigger than the `width` and `height`.

### Affected Lines
`checkerboard.c:99-100`, `checkerboard.c:110-111` and `checkerboard.c:122`

### Expected vs Observed
We expect the program to draw a partial square at the left and bottom of the generated picture. We observe a SEGV at line `checkerboard.c:122`.

### Steps to Reproduce
Put a `square_width` that does not divide the `width` or the `height`.

#### Command
```
./checkerboard output.png 100 100 8 00dead beef00
```

#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `checkerboard.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
Compute new boundaries for `x` and `y` after the calculation of `square_top_left_y`.
Then put these boundaries in the for-condition at lines `checkerboard.c:110-111`
