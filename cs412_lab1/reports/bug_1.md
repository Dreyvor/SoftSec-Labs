# TODO: FILL THE Description, Expected/Observed, Steps to reproduce, Command, Fix
# TODO: Correct it in code

### Name
Memory leak (non-freed malloc) and memory allocation is not checked after `solid.c:8`

### Description


### Affected Lines
`solid.c:16`, `solid.c:47-49`, `solid.c:130-132`, `solid.c:134-140`

### Expected vs Observed
I have to ask for that on Thursday.

### Steps to Reproduce
I didn't managed to crash to detect the bug

#### Command
I have to ask for that on Thursday.

#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `solid.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
Check the allocation after the line `solid.c:8` and free the memory (`palette` in this case) in case of an error (at the end of the function where the labels are).
