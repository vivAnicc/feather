#pragma once
#include "term.cpp"
#include "statement.cpp"
#include "../token.cpp"

class term_statement : public term {
    public:
        token open;
        std::vector<statement*> statements;
        token close;

        term_statement(token open, std::vector<statement*> statements, token close)
            : open (open), statements (statements), close (close) {}
        
        virtual std::vector<node*> get_children() {
            return std::vector<node*>(statements.begin(), statements.end());
        }

    protected:
        virtual std::vector<token> list_tokens() {
            return {
                open,
                close,
            };
        }
};