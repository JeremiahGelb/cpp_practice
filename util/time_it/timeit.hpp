#pragma once

#include <functional>

void timeit(std::function<void()> function, std::string function_name);