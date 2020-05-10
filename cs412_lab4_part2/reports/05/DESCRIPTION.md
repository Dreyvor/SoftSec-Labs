# Report BUG 00

### Name
Memory Leak

### Description
The program has a memory leak (non-freed memory at the end of the execution).

### Affected Lines
`pngparser.c:711` and `pngparser.c:730`

### Expected vs Observed
We expect to have no memory leaks. We observe that there is a memory leak on the `*img` in `load_png(...)`

### Steps to reproduce
#### Command
`./fuzzer_load_png leak_00`

#### Proof-of-Concept (if needed)
`leak_00`

### Suggested Fix Description
Add `if (*img) free(*img);` before `pngparser.c:711` and `pngparser.c:730`