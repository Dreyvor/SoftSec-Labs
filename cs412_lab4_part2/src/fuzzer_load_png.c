#include "pngparser.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// LibFuzzer stub
//

/*
  10.05.2020 Seems ok now
*/

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	//Added by assistant
  if (Size < 1000){ return 0; }

  struct image *test_img = NULL;

  int pid = getpid();

  char name[10];
  snprintf(name, 10, "%d", pid);

  FILE *input = fopen(name,"w");
  fwrite(Data, Size, 1, input);
  fclose(input);
  
  // What would happen if we run multiple fuzzing processes at the same time?
  // Take a look at the name of the file.
  load_png(name, &test_img);

  // Always return 0
  return 0;
}