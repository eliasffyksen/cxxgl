
#pragma once

#include <iostream>

#define ERR(x) std::cerr << ( x ) << std::endl

#if DEBUG
#define LOG(x) std::cout << ( x ) << std::endl
#else
#define LOG(x)
#endif
