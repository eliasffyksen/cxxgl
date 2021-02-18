
#pragma once

#include <iostream>

#define ERR(x) std::cerr << x << std::endl
#define FATAL_ERR(x) { ERR(x); exit(1); }

#if DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif
