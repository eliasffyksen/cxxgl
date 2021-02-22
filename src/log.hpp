
#pragma once

#include <iostream>

#if DEBUG
#define LOG(x) std::cout << x << std::endl
#define BREAK_IF(x) if(x) asm("int $3")
#else
#define LOG(x)
#define BREAK_IF(x)
#endif

#define ERR(x) std::cerr << "ERR: " << x << std::endl
#define FATAL_ERR(x) { ERR(x); BREAK_IF(true); }
