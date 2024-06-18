#pragma once
#include <string>
#include "bound_statement.cpp"

class bound_stmt_label : public bound_statement {
    public:
        std::string name;

        bound_stmt_label(std::string name) : name (name) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};