#pragma once
#include <vector>
#include <typeinfo>

class node {
    protected:
        virtual std::vector<token> list_tokens() = 0;
    public:
        virtual ~node() {}
        virtual std::vector<node*> get_children() = 0;
    std::vector<token> get_tokens() {
        std::vector<token> tokens = list_tokens();

        for (const auto& child : get_children()) {
            auto child_tokens = child->get_tokens();
            tokens.insert(tokens.end(), child_tokens.begin(), child_tokens.end());
        }

        return tokens;
    }
};