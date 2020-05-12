#include "pngparser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// LibFuzzer stub

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	
	// For this one I will try to separate Data as mentionned on Moodle
	// Firstly test if we have at least 2 bytes for the size of palette and image
	// Then we will 
	if (Size < 2){ return 0; }

	// I'll use the first byte (Data[0]) modulo 5 as the size of the palette
	uint8_t size_palette = (Data[0] % 5) + 1;
	struct pixel palette[size_palette];

	// I'll use the next byte (Data[1]) as the size of the palette
	struct image test_img;
	test_img.size_x = Data[1];
	test_img.size_y = Data[1];

	// Then I'll test Size to have enough Data (palette + img) + 2 due to size used before
	if (Size < sizeof(struct pixel) * (test_img.size_x * test_img.size_x + size_palette) + 2){
		return 0;
	}

	// Separate Data to fill palette
	for(size_t i = 0 ; i < size_palette ; i++){
		palette[i].red = Data[2 + i * sizeof(struct pixel)];
		palette[i].blue = Data[2 + i * sizeof(struct pixel) + 1];
		palette[i].green = Data[2 + i * sizeof(struct pixel) + 2];
		palette[i].alpha = Data[2 + i * sizeof(struct pixel) + 3];
	}

	// Palette is now filled. Let's do the same with test_img
	test_img.px = (struct pixel *) &Data[2 + (size_palette) * sizeof(struct pixel)];


	store_png("test_store_palette.png", &test_img, palette, size_palette);

	// Always return 0
	return 0;
} 