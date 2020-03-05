### Name
Memory management - (double free & `img` not freed)

### Description
`img->px` is freed twice.
`img` is not freed in case of `error_memory`.

### Affected Lines
`resize.c:84` and `resize.c:87`

### Expected vs Observed
The double free could corrupt the memory, we could encouter SEGV or other errors.

In addition `img` is not freed which leads to a memory leakage.

### Steps to Reproduce
You have to wait for an allocation to fail or simply you can force this behavior. To enforce this, replace `resize.c:49` by `if(1){`.
That's not really fair, but doing that will simulate the behavior if an allocation has failed and you has to go to the end and free everything.

#### Command
```
./resize_image poc.png output.png 2
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`.

### Suggested Fix Description
* Replace the second free `free(img->px)` at `resize.c:87` by `free(img)`.
* Set the pointers to NULL after they have been freed to avoid use-after-free.
