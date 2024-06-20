#pragma once
#include <optional>
#include "term.cpp"
#include "../token.cpp"

struct param {
    expression* expr;
    std::optional<token> comma;

    param (expression* expr, std::optional<token> comma)
        : expr (expr), comma (comma) {}
};

class term_call : public term {
    public:
        token ident;
        token open;
        std::vector<param> params;
        token close;

        term_call(token ident, token open, std::vector<param> params, token close)
            : ident (ident), open (open), params (params), close (close) {}
        
        virtual std::vector<node*> get_children() {
            std::vector<node*> v;
            for (const auto& p : params)
                v.push_back(p.expr);
            return v;
        }

    protected:
        virtual std::vector<token> list_tokens() {
            std::vector<token> v {
                ident,
                open,
            };
            for (const auto& p : params) {
                if (p.comma.has_value())
                    v.push_back(p.comma.value());
            }
            v.push_back(close);

            return v;
        }
};