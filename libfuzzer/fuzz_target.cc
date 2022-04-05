#include <stdlib.h>
extern "C" {
  #include <safestring/safe_mem_lib.h>
  #include <safestring/safe_str_lib.h>

  int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    char* dest = (char*) malloc(RSIZE_MAX_STR);
    memcpy_s(dest, RSIZE_MAX_STR, Data, Size);
    strtolowercase_s(dest, Size);
    free(dest);
    return 0;  // Non-zero return values are reserved for future use.
  }
}