# Report BUG 06

### Name
Attempting free on address which was not malloc()-ed

### Description
We try to free a an address that has not been malloc()-ed. This results in an error in AddressSanitizer (we used the flag "address" to compile).

### Affected Lines
`pngparser.c:953-954`

### Expected vs Observed
We observe a try to free an address that has not been allocated before. We expect to not attemping to free an address that has not been allocated.
In fact if we encounter a `pixel` which is not in `palette`, we `go to error` in `pngparser.c:946`. We still have not initialized `compressed_data_buf`
thus its value can be not `NULL` and we will try to free it in `error` (`pngparser.c:963-964`).

### Steps to reproduce
#### Command
`./fuzzer_store_png_palette -detect_leaks=0 ../reports/06/crash_06`

#### Proof-of-Concept (if needed)
`crash_06`

### Suggested Fix Description
Move `pngparser.c:953-954` after `pngparser.c:937`. Concerned lines:
```
uint8_t * compressed_data_buf = NULL;
uint32_t compressed_length;
```