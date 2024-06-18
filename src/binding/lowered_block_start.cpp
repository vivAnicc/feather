#pragma once
#include "bound_statement.cpp"

class lowered_block_start : public bound_statement {
    public:
        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};