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

### Bug 2: NAME

#### Description (2 points)

#### Proof of Concept (1 point)

#### Suggested Fix (1 point)

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