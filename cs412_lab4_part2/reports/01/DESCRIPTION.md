# Report BUG 01

## Note
This bug appears after you solved the `BUG_02`. Hence you have to apply the suggested fix for `BUG_02` and then read this one.

---

### Name
Memory Leak

### Description
The program has a memory leak (non-freed memory at the end of the execution).

### Affected Lines
`pngparser.c:709` and `pngparser.c:728`

### Expected vs Observed
We expect to have no memory leaks. We observe that there is a memory leak on the `ihdr_chunk->chunk_data`

### Steps to reproduce
#### Command
`./fuzzer_load_png ../reports/01/leak_01`

#### Proof-of-Concept (if needed)
`leak_01`

### Suggested Fix Description
Replace the lines `pngparser.c:709` and `pngparser.c:728`
by
```
if (ihdr_chunk){
        if(ihdr_chunk->chunk_data){
            free(ihdr_chunk->chunk_data);
        }
        free(ihdr_chunk);
    }
```
