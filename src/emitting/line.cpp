#pragma once
#include "instruction.cpp"
#include <variant>

class label {
    public:
        std::string name;
};

class line {
    public:
        std::variant<instruction, label, std::string, bool> content;

        const std::string to_string() {
            switch(content.index()) {
                case 0:
                    return std::get<instruction>(content).to_string();
                case 1:
                    return std::get<label>(content).name + ":";
                case 2:
                    return "; " + std::get<std::string>(content);
                case 3:
                    return "";
            }

            return "ERROR";
        }
};