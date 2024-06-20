#pragma once
#include <optional>
#include "statement.cpp"
#include "expression.cpp"
#include "../token.cpp"

class node_parameter {
    public:
        token type;
        token ident;
        std::optional<token> comma;

        node_parameter(token type, token ident, std::optional<token> comma = std::nullopt)
            : type (type), ident (ident), comma (comma) {}
};

class stmt_function : public statement {
    public:
        token type;
        token ident;
        token open;
        std::vector<node_parameter> params;
        token close;
        expression* body;
        token semi;

        stmt_function(token type, token ident, token open, std::vector<node_parameter> params, token close, expression* body, token semi)
            : type (type), ident (ident), open (open), params (params), close (close), body (body), semi (semi) {}
        
        virtual std::vector<node*> get_children() {
            return { body };
        }

    protected:
        virtual std::vector<token> list_tokens() {
            std::vector<token> v {
                type,
                ident,
                open,
            };

            for (const auto& param : params) {
                v.push_back(param.type);
                v.push_back(param.ident);
                if (param.comma.has_value()) {
                    v.push_back(param.comma.value());
                }
            }

            v.push_back(close);

            return v;
        }
};