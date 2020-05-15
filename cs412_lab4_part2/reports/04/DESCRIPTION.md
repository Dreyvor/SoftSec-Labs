# Report BUG 04

### Name
Closing non-existing file

### Description
When we give a name that is not valid to the `load_png(...)` the code try to open it, fail then goes to `error:` and try to close a file that has never been opened (thus equals `NULL`).

### Affected Lines
`pngparser.c:713`

### Expected vs Observed
We expect to not trying to close a file that has never been open. We observe that we try to close a file that has never been opened.

### Steps to reproduce
#### Command
`./fuzzer_load_png_name -detect_leaks=0 ../reports/04/crash_04`

#### Proof-of-Concept (if needed)
`crash_04`

### Suggested Fix Description
Test if the file we want to close has been opened. Replace `fclose(input)` by `if(input){ fclose(input); }`