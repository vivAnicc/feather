#pragma once
#include <string>

class bound_lvalue {
    public:
        virtual std::string get_address() = 0;
};