### Name
Invalid memory access (asking for write access)

### Description
The program wants to access invalid memory location (out of the picture) when the user try to draw a circle that goes out of the picture.
For example to draw a circle with radius 100 and centered at (5,5).

### Affected Lines
`circle.c:46-47`, `circle.c:54`, `circle.c:67-68` and `circle.c:75`

### Expected vs Observed
We expect the program to draw a circle centered at the given center with the perimeter in the given color.
The result observed is difficult to explain using words. It draws some parts of a circle but it could also crash with a SEGV.

### Steps to Reproduce
Enter coordinate 0,0 with a radius of 10

#### Command
```
./circle poc.png circle_poc.png 5 5 100 0cafe0
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`.

### Suggested Fix Description
Check the coordinates before using it in the loops and round.
