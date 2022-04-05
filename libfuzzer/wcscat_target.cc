#include <stdlib.h>
extern "C" {
  #include <safestring/safe_mem_lib.h>
  #include <safestring/safe_str_lib.h>

  int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Split Data in half to "dest + src"
    size_t dest_size = Size / 2;
    size_t src_size = Size / 2 + Size % 2;

    wchar_t dest[RSIZE_MAX_STR];
    wchar_t src[src_size];

    memcpy_s(dest, dest_size, Data, dest_size);
    memcpy_s(src, src_size, &(Data[dest_size]), src_size);
    
    wcscat_s(dest, RSIZE_MAX_STR, src);
    return 0;  // Non-zero return values are reserved for future use.
  }
}