#pragma once

#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace wci
{
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	//treci argument(predikat) je za sortiranje kljuceva, bice rasporedjeni od manjeg ka vecem
	template<typename keyType, typename valType, typename Pr = std::less<keyType>>
	using Map = std::map<keyType, valType, Pr>;

	template<typename keyType, typename valType, typename Hasher = std::hash<keyType>>
	using Dictionary = std::unordered_map<keyType, valType, Hasher>;

	template<typename T>
	using Set = std::unordered_set<T>;

	using uint8 = unsigned char;

	//## garantuje da ako se nista ne otpakuje iz ostalih argumenata da neci puci funkcija
	#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}