# TODO: FILL THE Description, Expected/Observed, Steps to reproduce, Command, Fix
# TODO: Separate into two bugs

### Name
Memory leak (non-freed malloc) and memory allocation is not checked after `solid.c:8`

### Description
(allocation) We have to check that we have enough memory to allocate `palette`

### Affected Lines
(allocation) `solid.c:8`
(memory leak) `solid.c:47-49`, `solid.c:130-132`, `solid.c:134-140`

### Expected vs Observed
(allocation) We expect the program to exit with an error if we don't have enough memory to allocate `palette`. We observe a SEGV.
(memory Leak) We expect no memory leak. We have memory leak.

### Steps to Reproduce
(allocation) Run a command with the `width < 0` on a machine that doesn't have enough memory for palette.
(memory leak) Run the code with ASAN using some option to detect thememory leakage

#### Command
(allocation)
```
./solid output.png -5 100 0cafe0
```

(memory leak)
```
./solid output.png 100 100 0cafe0
```

#### Proof-of-Concept Input (if needed)
(both) Nothing is needed for that bug as `solid.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
(allocation)Check the allocation after the line `solid.c:8`
(memory leak) Free the memory (`palette` in this case) everywhere it's needed, so at 3 places (no error, `error` and `error_mem `) (at the end of the function where the labels are).
