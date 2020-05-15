# Report BUG 03

### Name
Try to use a file that has not been opened

### Description
In `store_png(...)` we try to open a file with a given filename. This operation could fail.
In the case where we use fuzzer to generate `filename`, that will be a pretty shitty name thus it will crash and return `NULL`.
After that we will try to write in the `FILE` (that is `NULL` in our case) and it crashes.

### Affected Lines
`pngparser.c:736`

### Expected vs Observed
We expected to not write in a `NULL` pointer. We expect to test if a file has been correctly opened before trying to write into it.
We observed that the code try to open a file with a random shitty `filename` and then it crashes at `pngparser.c:736`.
However it creates a file with a strange filename.

### Steps to reproduce

#### Command
`./fuzzer_store_png_name -detect_leaks=0 ../reports/03/crash_03`

#### Proof-of-Concept (if needed)
`crash_03`

### Suggested Fix Description
Simply add `if (!output) { return 0; }` after the file opening in `pngparser.c:1026`
