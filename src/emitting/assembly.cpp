#pragma once
#include "line.cpp"
#include <sstream>
#include <vector>

class assembly {
    public:
        std::vector<line> lines;

        std::string all() {
            std::stringstream s;

            for (auto& line : lines) {
                s << line.to_string() << std::endl;
            }
            
            return s.str();
        }
};