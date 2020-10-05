#pragma once

#include <string>

namespace crypto
{
    int derive_key(std::string, char *);
    constexpr int output_len = 16;
};

