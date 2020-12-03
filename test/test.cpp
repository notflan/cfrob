#include <iostream>
#include <cstring>

#include <cfrob.hpp>

// Can be stored as `const char` array with compile-time size for optimal use.
const auto str			= "Hello world."_frob; 
constexpr const char* str2	= "Hello world."_frob;

// Can also be stored as normal `const char*` string constant pointer.
const char* str3		= "Hello world."_frob;

void assert_streq(const char* str, const char* str2)
{
	if (strcmp(str,str2)!=0)
	{
		std::cerr << "Mismatch: '" << str << "' is not eq to '" << str2 << "'" << std::endl;
		std::terminate();
	}
}

#define ASSERT_STREQ(ty, expr, get) do { ty _str = expr; assert_streq(_str get, str2); } while(0)

int main()
{
	char* str2 = strdup(str);
	memfrob(str2, strlen(str));

	std::cout << str << std::endl;
	std::cout << str2 << std::endl;

	// test of frob::*frob()
	{
		ASSERT_STREQ(const auto, frob::strfrob(str), .c_str()); 
		std::string frobbed = frob::strfrob((const char*)str2);

		constexpr const auto out = frob::strfrob<>("Hello world."); //for some reason it doesn't prefer the `constexpr` template overload, even in a constexpr context?
		auto out2 = frob::strfrob(out);
		std::cout << frobbed << std::endl;
		std::cout << out << std::endl;
		std::cout << out2 << std::endl;
	}

	free(str2);
	return 0;
}
