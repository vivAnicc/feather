#pragma once
#include "../binding/binder.cpp"
#include "statement_lowering.cpp"
#include "expression_lowering.cpp"

class lowerer {
    bound_stmt_block* block;

    public:
        lowerer(bound_stmt_block* block) : block (block) {}

        std::vector<bound_statement*> lower() {
            return lower_statement(block);
        }
};