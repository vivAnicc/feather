#pragma once
#include "bound_statement.cpp"

class bound_stmt_goto : public bound_statement {
    public:
        std::string label;

        bound_stmt_goto(std::string label) : label (label) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};