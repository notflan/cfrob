#pragma once


#include <string>
#include <vector>

namespace frob
{
	using u8 = unsigned char;
	constexpr static const u8 ROT13_CONSTANT =
#ifdef FROB_CONSTANT
	(u8)(FROB_CONSTANT)
#else
	(u8)42;
#endif
	constexpr inline u8 rot13(u8 i)
	{
		return i ^ ROT13_CONSTANT;
	}

	template<std::size_t N, typename CHAR=char>
		requires(N > 0)
	struct cfrob
	{
		CHAR out[N]{};
		inline constexpr operator const char*() const { return out; }
		inline operator char*() { return out; }

		constexpr cfrob(const CHAR (&sz)[N])
		{
			for(std::size_t i=0;i<N-1;i++)
				out[i] = rot13((u8)sz[i]);
			out[N-1] = 0;
		}
	};

	// frobnicate functions
	template<std::size_t N>
	constexpr auto memfrob(const u8 (&sz)[N])
	{
		return cfrob(sz);
	}
	template<std::size_t N>
	inline auto memfrob(u8 (&sz)[N])
	{
		for(std::size_t i=0;i<N;i++)
			sz[i] = rot13(sz[i]);
		return sz;
	}
	template<typename P = void>
	inline P* memfrob(u8* ptr, std::size_t len)
	{
		for(auto i=0;i<len;i++)
			ptr[i] = rot13(ptr[i]);
		return (P*)ptr;
	}
	inline std::vector<u8> memfrob(const u8* ptr, std::size_t len)
	{
		std::vector<u8> out;
		out.reserve(len);
		
		for(std::size_t i=0;i<len;i++)
			out.push_back(rot13(ptr[i]));
		return out;
	}
	inline std::vector<u8>& memfrob(std::vector<u8>* _s)
	{
		std::vector<u8>& s = *_s;
		for(auto& b : s) b = rot13(b);
		return s;
	}
	inline std::vector<u8> memfrob(const std::vector<u8>& s)
	{
		std::vector<u8> out = s;
		memfrob(out);
		return out;	
	}

	template<std::size_t N>
	constexpr inline auto strfrob(const char (&sz)[N])
	{
		return cfrob(sz);
	}
	inline std::string strfrob(const std::string& s)
	{
		std::string out;
		out.reserve(s.size());
		for(const char& c : s)
			out+= rot13((u8)c);
		return out;
	}
	inline std::string& strfrob(std::string* sp)
	{
		std::string& s = *sp;
		for(char& c : s)
			c = rot13((u8)c);
		return s;
	}
	inline std::string strfrob(const char* str)
	{
		return strfrob(std::string(str));
	}
	inline char* strfrob(char* str)
	{
		for(;*str;str++)
			*str = rot13((u8)*str);
		return str;
	}
	
}


template<frob::cfrob C>
constexpr auto operator "" _frob()
{
	return C.out;
}

