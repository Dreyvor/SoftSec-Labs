# Bug Report

## Solid.c
### Bug 1
#### Name
Command injection

#### Description
The user is able to put an output name of at most 500 characters. Then the program execute the following command (lines 120-122):
```
stat -c %s outputNameChosenByUser
```
As the output name is not sanitized, the user is able execute whatever he wants.

#### Affected Lines
In `solid.c:122`

#### Expected vs Observed
We expect that the program gives the size of the output without executing any specific command injected as described above.

#### Steps to Reproduce

##### Command
```
./solid "solid;whoami" 100 100 00ffff
```
##### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `solid.c` generates an output.

#### Suggested Fix Description
We have to sanitize the output name given by the user. First step is to avoid the semicolons and possibilities of pipes.

---
### Bug 2

