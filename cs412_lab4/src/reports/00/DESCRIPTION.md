# Report BUG 00

### Name
Not consistent with the documentation

### Description
The value returned by `load_png` is 0 if there is no error and 1 otherwise. The problem is in `size.c:16`.
If `load_png` return 0, then we return 1. We have to continue the execution instead of returning 1.

### Affected Lines
`size.c:16`

### Expected vs Observed
If `load_png` return 0, then we return 1. We have to continue the execution instead of returning 1.

### Steps to reproduce
Run the following command with `poc00.png`

#### Command
`./size reports/00/poc00.png`

#### Proof-of-Concept (if needed)
`poc00.png`

### Suggested Fix Description
We could simply modify  `size.c:16` and replace it by `if (load_png(input_name, &img)) {`
