# Report: Fuzzing


## Fuzzing stub


## Setup and Methodology


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

### Bug 3: NAME

#### Description (2 points)

#### Proof of Concept (1 point)

#### Suggested Fix (1 point)

---

### Bug 4: NAME

#### Description (2 points)

#### Proof of Concept (1 point)

#### Suggested Fix (1 point)

---

### Bug 5: NAME

#### Description (2 points)

#### Proof of Concept (1 point)

#### Suggested Fix (1 point)