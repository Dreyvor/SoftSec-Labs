# TODO: CHECK LINES

### Name
Local pointer returned (Unallocated memory)

### Description
To return a pointer from a function we have to be sure that the pointer life-time is not only local to the function.
(i.e. you have to use a `malloc` when you return a pointer).

### Affected Lines
`filter.c:101-102`

Due to these lines it pops an error when we use this function and try to use the returned value
(e.g. at lines `filter.c:143-146` because `neg` is the value return by the previously described function).

### Expected vs Observed
We expect the value returned by `get_pixel` not to be `NULL` (i.e. `0x0`).
As we do not allocate memory on the heap but only put it on the stack, when
return from that function, the stack is poped and the pointer value is lost and
set to `0x0`.

### Steps to Reproduce
Simply run `filter` while asking for a negative filter.

#### Command
```
./filter poc.png output.png negative
```

#### Proof-of-Concept Input (if needed)
`poc.png` is needed. This file is generated using `./checkerboard poc.png 100 100 10 00dead beaf00`.

### Suggested Fix Description
Allocate the memory for the value returned by the function `get_pixel()` at `filter.c:101-102`.
We can use a simple malloc and verifying the allocation before returning the result.
