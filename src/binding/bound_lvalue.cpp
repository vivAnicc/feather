#pragma once
#include <string>
#include "../emitting/operand.cpp"

class bound_lvalue {
    public:
        virtual operand get_address() = 0;
};