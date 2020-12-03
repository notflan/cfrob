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
#include <cstring>

auto string2 = strdup(easter_egg);
memfrob(string2, strlen(easter_egg));
// `string2` now contains the string "Something cool"
free(string2);
```

## Functions

Also provided are `memfrob()` and `strfrob()` functions of our own for both strings and binary data, which do the same as libc `memfrob()`.

``` c++
/// `memfrob()`
{
  const unsigned char data[] = {
    0xa, 0xd, 0x10, 0xf7,
  };

  const auto ctime = forb::memfrob(data); // Done at compile time, like the literal.

  const std::vector<unsigned char> cloned = frob::memfrob(data, sizeof(data)); // Clone constant data at runtime into a new `std::vector<unsigned char>`.

  unsigned char* data2 = malloc(10);
  frob::memfrob(data2, 10); // Mutated in place
  free(data2);

  const std::vector<unsigned char> xvec{0xad, 0xb, 0xc};
  std::vector<unsigned char> xfrobbed = frob::memfrob(xvec); // Cloned;

  std::vector<unsigned char> vec{0xad, 0xb, 0xc};
  frob::memfrob(&vec); // Mutated `vec` in place. (explicit pointer is used here so you know it's not mutating when you might not expect.) 
}
/// `strfrob()`
{
  const char* string= "const";
  std::string frobbed = frob::strfrob(string); // Cloned

  char* string2 = "mutated";
  frob::strfrob(string2); // Mutated in plate

  const std::string xstring = "stl const string"s;
  std::string xfrobbed = frob::strfrob(xstring); // Cloned

  std::string xstring2 = "stl mutate string";
  frob::strfrob(&xstring2); // Mutated in plate (explicit pointer is used here so you know it's not mutating when you might not expect.)

  constexpr const auto ctime = frob::strfrob<>("done at comptime, like the literal `_frob`"); // Explicit template `<>` is required here otherwise it overloads to the non `constexpr` functions, even in a `constexpr` context;
}


```

# Test
Run `make test` to build and run the test that ensures the original string literal does not appear anywhere in the outputted binary. 

# License
Public domain.
