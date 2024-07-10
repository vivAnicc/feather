#pragma once
#include "bound_statement.cpp"
#include "bound_scope.cpp"

class lowered_block_start : public bound_statement {
    public:
        bound_scope* scope;

        lowered_block_start(bound_scope* scope) : scope (scope) {}

        virtual std::vector<bound_node*> get_children() {
            return {};
        }
};