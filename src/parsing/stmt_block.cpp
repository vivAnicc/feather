#pragma once
#include "statement.cpp"
#include "../token.cpp"

class stmt_block : public statement {
    public:
        token open;
        std::vector<statement*> statements;
        token close;

        stmt_block(token open, std::vector<statement*> statements, token close) 
            : open (open), statements (statements), close (close) {}
        
        virtual std::vector<node*> get_children() {
            return std::vector<node*>(statements.begin(), statements.end());
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                open,
                close
            };
        }
};