#pragma once

#include <string_view>
#include <string>

namespace pacc {
    class Compiler {
    public:
        std::string  compile(std::istream& input);
    };
}

