#pragma once
#include <optional>
#include "asm_register.cpp"
#include <string>

class operation {
    public:
        asm_size* size;
        std::optional<asm_register*> base;
        std::optional<asm_register*> index;
        std::optional<int> scale;
        std::optional<int> displace;

        std::string to_string() {
            std::string s = size->name + " [";

            if (displace && !base && !index && !scale) {
                s += std::to_string(displace.value());
            }
            else if (!displace && base && !index && !scale) {
                s += base.value()->name;
            }
            else if (!displace && base && index && scale) {
                s += base.value()->name + " + " + index.value()->name + " * " + std::to_string(scale.value());
            }
            else if (!displace && base && index && !scale) {
                s += base.value()->name + " + " + index.value()->name;
            }
            else if (displace && base && !index && !scale) {
                s += base.value()->name + " + " + std::to_string(displace.value());
            }
            else if (displace && base && index && scale) {
                s += base.value()->name + " + " + index.value()->name + " * " + std::to_string(scale.value()) + " + " + std::to_string(displace.value());
            }

            return s + "]";
        }
};