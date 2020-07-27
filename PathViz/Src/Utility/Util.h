#pragma once

#include <iostream>

#define PRINT(x) (std::cout << x)
#define PRINTLN(x) (PRINT(x) << std::endl)
#define ASSERT(x) if (!(x)) __debugbreak();