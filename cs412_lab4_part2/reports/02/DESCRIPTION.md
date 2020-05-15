# Report BUG 02

### Name
Double Free

### Description
We double free a variable.

### Affected Lines
`pngparser.c:301` and `pngparser.c:721`

### Expected vs Observed
We expect to exit nicely and no double free. We observe a double free.

### Steps to reproduce
#### Command
`./fuzzer_load_png -detect_leaks=0 ../reports/02/crash_02`

#### Proof-of-Concept (if needed)
crash_02

### Suggested Fix Description
Simply add `chunk->chunk_data = NULL;` after `pngparser.c:301`

# Note
Note that using the command provided in this bug report still generates an error `LeakSanitizer: detected memory leaks`. I decided to put that new issue in an other report because it is not really the same bug.