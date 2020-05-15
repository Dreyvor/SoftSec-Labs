# Report BUG 05

### Name
Memory Leak

### Description
The program has a memory leak (non-freed memory at the end of the execution). It's a direct leak of 40100 bytes.

### Affected Lines
`pngparser.c:916` (line of the return)

### Expected vs Observed
We expect to have no memory leaks. We observe that there is a memory leak on `non_compressed_buf` in `store_idat_rgb_alpha(...)`

### Steps to reproduce
#### Command
`./fuzzer_store_png_rgba ../reports/05/leak_05`

#### Proof-of-Concept (if needed)
`leak_05`

### Suggested Fix Description
Add `free(non_compressed_buf);` before `pngparser.c:916`