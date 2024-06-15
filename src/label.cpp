#pragma once
#include <string>

unsigned long label_idx = 0;

std::string get_label(std::string name = "label") {
    return name + std::to_string(label_idx++);
}