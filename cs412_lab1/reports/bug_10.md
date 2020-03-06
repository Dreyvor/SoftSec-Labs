### Name
Memory allocation is not checked after `solid.c:8`

### Description
We have to check that we have enough memory to allocate `palette`

### Affected Lines
`solid.c:8`

### Expected vs Observed
We expect the program to exit with an error if we don't have enough memory to allocate `palette`. We observe a SEGV.

### Steps to Reproduce
Run a command with the `width < 0` on a machine that doesn't have enough memory for palette.

#### Command
```
./solid output.png -5 100 0cafe0
```

#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `solid.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
Check the allocation after the line `solid.c:8`
