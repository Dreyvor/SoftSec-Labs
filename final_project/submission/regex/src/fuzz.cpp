#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdint.h>
#include "re.h"

extern "C"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{

    /**
     * The regex engine is comprised of two components:
     * - the parser
     * - the processor
     * In this stub, you are expected to fuzz both components simultaneously,
     *   in order to keep the implementation simple.
     *
     * The interface to access the parser is the function declared as:
     *   RegularExpression * parse(const char * str, size_t len, int * err);
     * `str` is a character array of length `len`. `err` is a pointer to an int
     *   where the resulting error (0 == no error) is stored.
     * The parser returns a `RegularExpression` object which can be fed to the
     *   search component in order to scan a text for the first pattern match.
     *
     * The interface to access the processor is the object declared as:
     *   SearchExpression(RegularExpression *regex);
     *   std::tuple<int, int> SearchExpression::search(const char * str, unsigned int len);
     * `regex` is the pointer to the RegularExpression object created by the
     *   parser. `SearchExpression` takes ownership of this object, and thus, it
     *   should not be manually free'd after construction.
     * `str` is the excerpt of text in which to search for an occurence of the
     *   regex pattern, and `len` is its length. The `search` function returns
     *   an int tuple of (index of match, length of match). These can be
     *   accessed as std::get<0>(result) and std::get<1>(result), respectively.
     * For the purposes of this fuzzer, we are not interested in the result, but
     *   rather in the input validation and error-handling of the regex engine.
     *
     * Write your libFuzzer stub here, where you first split the input `Data`
     *   buffer into two strings, `pattern` and `text`, then feed those inputs
     *   into the corresponding interfaces.
     * It remains up to you how to split the input to maximize the chance of
     *   finding bugs.
     *
     * All non-crashing execution paths must terminate with `return 0;`. All
     *   other return values may be reserved by the fuzzer.
     *
     * Triage and attempt to fix bugs as you encounter them. This will speed up
     *   your fuzzing process as it only encounters crashes for the remaining
     *   bugs.
     */

	size_t size_regex = 128;

	if(Size < size_regex){ return 1; } // TODO : AFL 1 vs LibFuzzer 0

	int err = 0;

    char *regex_txt = (char*) malloc(size_regex);
    memcpy(regex_txt, Data, size_regex);

	RegularExpression* regex = parse(regex_txt, size_regex, &err);
    if(err == 0){
	   SearchExpression(regex).search((const char *) (Data + size_regex), Size - size_regex);
    }

    free(regex_txt);

	return 0;
}

int main(int argc, char **argv) {
  fprintf(stderr, "StandaloneFuzzTargetMain: running %d inputs\n", argc - 1);

  int ret = 0;

  for (int i = 1; i < argc; i++) {
    fprintf(stderr, "Running: %s\n", argv[i]);
    FILE *f = fopen(argv[i], "r");
    assert(f);
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *buf = (unsigned char*)malloc(len);
    size_t n_read = fread(buf, 1, len, f);
    fclose(f);
    assert(n_read == len);
    
    //MY STUB

    ret = LLVMFuzzerTestOneInput(buf, len);

    //END OF MY STUB

    free(buf);
    fprintf(stderr, "Done:    %s: (%zd bytes)\n", argv[i], n_read);
  }
  return ret;
}
