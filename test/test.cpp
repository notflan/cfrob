#include <iostream>
#include <cstring>

#include <cfrob.hpp>

// Can be stored as `const char` array with compile-time size for optimal use.
const auto str			= "Hello world."_frob; 
constexpr const char* str2	= "Hello world."_frob;

// Can also be stored as normal `const char*` string constant pointer.
const char* str3		= "Hello world."_frob;

int main()
{
	char* str2 = strdup(str);
	memfrob(str2, strlen(str));

	std::cout << str << std::endl;
	std::cout << str2 << std::endl;	
	free(str2);

	return 0;
}
