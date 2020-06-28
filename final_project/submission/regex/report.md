# Report: Fuzzing


## Fuzzing stub
We used AFL so the stub had to be encapsulated in a main function. 

## Setup and Methodology
Our fuzzer stub uses regex of 128 bytes. At the beginning it checks if the given `Data` are bigger than 128 bytes. Otherwise we tell the fuzzer that he has to increase the size of `Data`. Then we read the first 128 bytes and consider these as the regex (i.e. send them to `parse`). If no error occurs, we call `search` to search the text (i.e. rest of `Data`).

The `main` has been taken from [llvm-project GitHub](https://github.com/llvm/llvm-project/blob/master/compiler-rt/lib/fuzzer/standalone/StandaloneFuzzTargetMain.c) and adapted for our stub.

The seeds was some correct and working regex with some text. Some was small, others was really big. We tried to use most of the regex capabilities (e.g. "^helloThere$" or "([abcx-z]|de)?"). The seeds we used found the bugs we submitted.

We directly tried AFL and it found the bugs (sometimes after a while). We corrected the bugs one after one (while correcting them between two session of fuzzing).

The parameters used for AFL was the default ones.

---

## Bug reports

### Bug 1: Recursive delete

#### Description (2 points)
There is a deletion of `next` at `parse.cpp:239`. The problem is that we add `next` to a linked list in the object `head` in its attribute `next_`.
At the moment we delete `head` at `parse.cpp:235`, we also recursively delete its `next_` attribute. This is a problem since we try to delete its last item second time (`parse.cpp:239`). 

#### Proof of Concept (1 point)
`BUG_01` is located in `regex/poc` folder

#### Suggested Fix (1 point)
We have to delete `next` only if `delete head` has not delete this one before.
We can replace `parse.cpp:238` by
```c++
else if (next != nullptr) {
```

---

### Bug 2: AddressSanitizer: heap-buffer-overflow

#### Description (2 points)
**After we applied the correction of the first bug (Bug 1)**, we discover a second bug with the same input.

This bug is a heap-buffer-overflow. At `parse.cpp:164` we try to read `stmp` for the switch. However when we already read the whole regex (e.g. assume the regex is the 128 first bytes, then we read 128 bytes and arrive at `parse.cpp:164`) we want to read the byte 129. This reading results in a heap-buffer-overflow.

#### Proof of Concept (1 point)
`BUG_02` is located in `regex/poc` folder (same POC as precedent bug)

#### Suggested Fix (1 point)
Only do the second switch (i.e. `parse.cpp:164`) if `ltmp > 0`. Add `if(ltmp > 0){` before `parse.cpp:164` and `}` after `parse.cpp:214`.

---

### Bug 3: Failed assert

#### Description (2 points)
In `LazyRepeatRangeExpression.cpp:26`, `mlen_regex` is set to `1` if the "regex element" (e.g. `LiteralExpression`) matches the string and to `-1` otherwise.
Knowing that, in `LazyRepeatRangeExpression.cpp:29` we can simply add `mlen_regex` to `mlen` instead of `mlen_regex + 1`.

#### Proof of Concept (1 point)
`BUG_03` is located in `regex/poc` folder

#### Suggested Fix (1 point)
Replace `LazyRepeatRangeExpression.cpp:29` by
```c++
mlen += mlen_regex;
```

---

### Bug 4: Really long hang

#### Description (2 points)
The code hangs during a really long time which is not a normal behaviour. The input given is filled with a **lot** of `+` and `*`.

#### Proof of Concept (1 point)
`BUG_04` is located in `regex/poc` folder

#### Suggested Fix (1 point)
Sadly, we did not found any fix for this one

---

### Bug 5: Malloc too big

#### Description (2 points)
The problem occurs when the repetition of a pattern is too big (i.e. `(pattern){$BIG_NUMBER}`). The malloc occurs in `parse.cpp:96` (i.e. The code tries to allocate too much memory). Thus, it receives a `SIGKILL` error which kill the execution of the program (after some laggy mouse pointer).

#### Proof of Concept (1 point)
`BUG_05` is located in `regex/poc` folder

#### Suggested Fix (1 point)
Use a boundary to limit the number of maximum repetition in the constructor of `RepeatNExpression`. It could be something like:
* At the beginning of the file `RegularExpression.h`
```c++
#define MAX_REPEAT 500
```
* After `RegularExpression.cpp:7`:
```c++
if (N > MAX_REPEAT){
	exit(1);
}
```