# Report BUG 00

### Name
Memory Leak

### Description
The program has a memory leak (non-freed memory at the end of the execution).

### Affected Lines
`pngparser.c:711` and `pngparser.c:730` (lines of the return statement)

### Expected vs Observed
We expect to have no memory leaks. We observe that there is a memory leak on `inflated_buf` in `load_png(...)`

### Steps to reproduce
#### Command
`./fuzzer_load_png leak_00`

#### Proof-of-Concept (if needed)
`leak_00`

### Suggested Fix Description
Add `if (inflated_buf) free(inflated_buf);` before `pngparser.c:711` and `pngparser.c:730`
