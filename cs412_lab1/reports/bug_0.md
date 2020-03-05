### Name
Command injection

### Description
The user is able to put an output name of at most 500 characters. Then the program execute the following command (lines 120-122):
```
stat -c %s outputNameChosenByUser
```
As the output name is not sanitized, the user is able execute whatever he wants by using `;` or `|` for example.

### Affected Lines
In `solid.c:122`

### Expected vs Observed
We expect that the program gives the size of the output without executing any specific command injected as described above.

### Steps to Reproduce

#### Command
```
./solid "solid;whoami" 100 100 0cafe0
```
#### Proof-of-Concept Input (if needed)
Nothing is needed for that bug as `solid.c` generates an output and doesn't take any file as input.

### Suggested Fix Description
We have to sanitize the output name given by the user. A possibility for that is to use `syscall` instead of `system`.
Another way, the one we used here is to use `lstat` with the `struct stat`. If you want to have more info about that,
use the command `man 2 stat`.
