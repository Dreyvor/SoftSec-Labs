#include "pngparser.h"
#include <stdio.h>
#include <string.h>

// LibFuzzer stub
//

/*
  10.05.2020 Seems ok now
  Don't run it. It creates many shitty files. Have fun ;)
*/

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1000){ return 0; }

  struct image test_img;
  struct pixel px;

  test_img.size_x = 1;
  test_img.size_y = 1;
  test_img.px = &px;

  px.red = 123;
  px.green = 123;
  px.blue = 123;
  px.alpha = 123;
  
  store_png(Data, &test_img, NULL, 0);

  // Always return 0
  return 0;
}