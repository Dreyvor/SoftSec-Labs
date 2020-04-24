# Report BUG 01

### Name
Double free

### Description
We free two times the variable `chunk->chunk_data`. First in `pngparser.c:300` and secondly in `pngparser.c:719`

### Affected Lines
`pngparser.c:300`, `pngparser.c:712`

### Expected vs Observed
We expected the program to free the memory and exit. Instead the program try to double free the memory because a pointer has not been set to `NULL` after been freed.

### Steps to reproduce
#### Command
`./size reports/01/poc01.png`

#### Proof-of-Concept (if needed)
`poc01.png`

### Suggested Fix Description
Set the pointer to free after freeing it in `pngparser.c:300`. After `pngparser.c:300` add `chunk->chunk_data = NULL;`
