# TODO: Fix the code

### Name
Stack Based Buffer Overflow due to an unverified input size.

### Description
Same idea as `bug_8.md`. The arguments `argv[i]` $i\in\{1,2\}$ are copied into `input` and `output` which are an arrays of size 256 but the size of `argv[i]` are not checked.

### Affected Lines
`rect.c:20-21`

### Expected vs Observed
The expected behavior for a function is to end without an `core dumped` (either with a success or exiting with an error code).

### Steps to Reproduce
Use the `rect` command with an argument's size bigger than 256 characters as input (or output) name.

#### Command
`./rect poc.png long_output_name111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 0 0 30 30 0cafe0
`

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`

### Suggested Fix Description
Use `strncpy(...)` instead of `strcpy(...)` in order to avoid stack based buffer overflows during the copy of the arguments.
