#pragma once

namespace frob
{
	using u8 = unsigned char;
	constexpr u8 rot13(u8 i)
	{
		return i ^ (u8)42;
	}

	template<std::size_t N>
	struct cfrob
	{
		char out[N]{};
		constexpr cfrob(const char (&sz)[N])
		{
			for(std::size_t i=0;i<N-1;i++)
				out[i] = rot13((u8)sz[i]);
			out[N-1] = 0;
		}
	};
	template<>
	struct cfrob<0>
	{
		char out[0]{};
	};
}

template<frob::cfrob C>
constexpr auto operator "" _frob()
{
	return C.out;
}

