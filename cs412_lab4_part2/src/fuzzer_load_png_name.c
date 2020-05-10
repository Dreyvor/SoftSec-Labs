#include "pngparser.h"
#include <stdio.h>

// LibFuzzer stub
//

/*
	10.05.2020 Seems ok now
*/
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct image *img = NULL;
  int contains_00 = 0;

  for(int i=0; i<Size && contains_00 == 0 ; i++){
  	if(Data[i] == '\x00'){
  		contains_00 = 1;
  	}
  }
  
  if(!contains_00) { return 0; }

  load_png(Data, &img);

  // Always return 0
  return 0;
}