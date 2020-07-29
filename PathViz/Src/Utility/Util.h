#pragma once

#include <iostream>
#include <unordered_map>

#define PRINT(x) (std::cout << x)
#define PRINTLN(x) (PRINT(x) << std::endl)
#define ASSERT(x) if (!(x)) __debugbreak();

template<typename K, typename V>
inline void put(std::unordered_map<K, V>& map, K key, V value) {
	map.emplace(key, value).first->second = value;
}