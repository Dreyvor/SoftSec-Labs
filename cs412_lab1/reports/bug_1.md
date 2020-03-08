### Name
Memory leak (non-freed malloc)

### Description
If we allocate something on the heap, we have to free it at the end of the program in order to avoid memory leak.

### Affected Lines
`solid.c:47-49`, `solid.c:130-132`, `solid.c:134-140`

### Expected vs Observed
We expect no memory leak. We have memory leak with `struct pixel *palette`.

### Steps to Reproduce
Compile the code with ASAN using some option to detect the memory leaks.

#### Command
```
./solid output.png 100 100 0cafe0
```

#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `solid.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
Free the memory (`palette` in this case) everywhere it's needed. In this code we need to free it at 3 places (no error, `error` and `error_mem`) (at the end of the function where the labels are).
