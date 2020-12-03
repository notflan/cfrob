#include <iostream>
#include <cstring>

#include <cfrob.hpp>

const auto str = "Hello world."_frob;

int main()
{
	char* str2 = strdup(str);
	memfrob(str2, strlen(str));

	std::cout << str << std::endl;
	std::cout << str2 << std::endl;	
	free(str2);

	return 0;
}
