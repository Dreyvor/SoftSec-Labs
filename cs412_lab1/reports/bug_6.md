# TODO: Fix the code

### Name
Memory allocation not checked

### Description
The memory allocation of `new_img->px` at `resize.c:47` is not checked.

### Affected Lines
`resize.c:47`

### Expected vs Observed
If `malloc` isn't able to allocate the space requested we expect an error message.

### Steps to Reproduce
If you run the code while your memory is full (RAM + swap), you could encouter an error.

#### Command
```
./resize_image poc.png output.png 2
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`.


### Suggested Fix Description
Add a check `!new_img->px` using the same idea that the one for `!img->px` at `resize.c:49-51`
