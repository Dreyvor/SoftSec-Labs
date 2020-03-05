### Name
Stack Based Buffer Overflow due to an unverified input size.

### Description
The arguments `argv[i]` are copied into `arg` which is an array of size 256 but the size of `argv[i]` is not checked.

### Affected Lines
`filter.c:177-179` and `filter.c:183`

### Expected vs Observed
The expected behavior for a function is to end without an `core dumped` (either with a success or exiting with an error code).

### Steps to Reproduce
Use the `filter` command with an argument's size bigger than 265 characters as filter name

#### Command
```
./filter poc.png output.png grayscaleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`

### Suggested Fix Description
Check the length of the arguments before the copy in order to avoid stack based buffer overflows during the copy of the arguments.
