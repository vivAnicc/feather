#pragma once
#include <optional>
#include "statement.cpp"
#include "expression.cpp"
#include "type.cpp"
#include "../token.cpp"

class node_parameter {
    public:
        type* t;
        token ident;
        std::optional<token> comma;

        node_parameter(type* t, token ident, std::optional<token> comma = std::nullopt)
            : t (t), ident (ident), comma (comma) {}
};

class stmt_function : public statement {
    public:
        token function;
        token ident;
        token open;
        std::vector<node_parameter> params;
        token close;
        expression* body;
        token semi;

        stmt_function(token function, token ident, token open, std::vector<node_parameter> params, token close, expression* body, token semi)
            : function (function), ident (ident), open (open), params (params), close (close), body (body), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            std::vector<node*> v;
            for (const auto& param : params) {
                v.push_back(param.t);
            }
            v.push_back(body);
            return v;
        }

    protected:
        virtual std::vector<token> list_tokens() {
            std::vector<token> v {
                function,
                ident,
                open,
            };

            for (const auto& param : params) {
                v.push_back(param.ident);
                if (param.comma.has_value()) {
                    v.push_back(param.comma.value());
                }
            }

            v.push_back(close);

            return v;
        }
};