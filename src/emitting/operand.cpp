#pragma once
#include <variant>
#include <string>
#include "asm_register.cpp"
#include "operation.cpp"

class operand {
    public:
        std::variant<asm_register*, int, std::string, char*, operation> val;

        std::string to_string() {
            switch (val.index())
            {
            case 0:
                return std::get<asm_register*>(val)->name;
            case 1:
                return std::to_string(std::get<int>(val));
            case 2:
                return "\"" + std::get<std::string>(val) + "\"";
            case 3:
                return std::get<char*>(val);
            case 4:
                return std::get<operation>(val).to_string();
            }

            return "ERROR";
        }

        operand(asm_register* r) : val(r) {}
        operand(int n) : val(n) {}
        operand(operation o) : val(o) {}
        operand(std::string s, bool string = false) {
            if (string)
                val = s;
            val = s.c_str();
        }
};