# Compile-time `memfrob()`

glibc has a function in `string.h` called `memfrob()` which applies ROT13 to an arbitrary byte buffer.
This small C++20 header allows you to do this at compile time to trivially obscure string literals without the literal itself appearing in the binary anywhere at all.

# Usage
The literals can be created and stored as a sized `char` array, or as a C string pointer.

``` c++
#include "cfrob.hpp"

const auto easter_egg = "Something cool"_frob;
const char* c_like_easter_egg = "Something cool"_frob;
```

To reverse just apply ROT13 on to the string again.

``` c++
auto string2 = strdup(easter_egg);
memfrob(string2, strlen(easter_egg));
// `string2` now contains the string "Something cool"
free(string2);
```

## Test
Run `make test` to build and run the test that ensures the original string literal does not appear anywhere in the outputted binary. 

# License
Public domain.
