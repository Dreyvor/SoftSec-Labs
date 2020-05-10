#include "pngparser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1000){ return 0; }

  struct image *test_img = NULL;

  /*
  int pid = getpid();

  char name[10];
  snprintf(name, 10, "%d", pid);
  */

  char *name="test_file.png";

  FILE *input = fopen(name,"w");
  fwrite(Data, Size, 1, input);
  fclose(input);
  
  // What would happen if we run multiple fuzzing processes at the same time?
  // Take a look at the name of the file.
  load_png(name, &test_img);

  store_png("test_store_rgba.png", &test_img, NULL, 0);

  // Always return 0
  return 0;
}