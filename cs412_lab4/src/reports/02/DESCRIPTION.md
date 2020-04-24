# Report BUG 02

### Name
Type confusion + Allocation not verified

### Description
Firtsly the size used for the image width and height is not consistent with the specification. The specification explains that the width and the height are set in the file using 4 bytes = 32 bits.
We have to change that in `pngparser.h`

Secondly we don't verify the allocations in the function `convert_color_palette_to_image` in `pngparser.c`.

### Affected Lines
`pngparser.h:46-47`, `pngparser.c:418`, `pngparser.c:421`

### Expected vs Observed
Firstly we want the image's sizes to be on 32 bits according to the specification. It was defined using `uint16_t` in `pngparser.h`.

Secondly we expect a proper way to handle allocation problems. We observe that the program totally fail when he try to access a pointer set to NULL by allocation problems.

### Steps to reproduce


#### Command
`./size reports/02/poc02.png`

#### Proof-of-Concept (if needed)
poc02.png

### Suggested Fix Description
Firstly modify `pngparser.h:46-47` to use `uint32_t` instead of `uint16_t`

Secondly we verify the allocations with something like `if(!img) { goto error; }` after `pngparser.c:418` and with `if(!img->px) { goto error; }` after `pngparser.c:421`

Thirdly we define the error label. We free `img` and `img->px` if they are not NULL.
