#pragma once
#include <map>
#include <ranges>
#include "../symbols/function_symbol.cpp"

class bound_scope {
    public:
        std::map<std::string, variable_symbol*> variables;
        std::map<std::string, function_symbol*> functions;
        bound_scope* parent;
        int var_offset;

        bound_scope(bound_scope* parent = nullptr) : parent (parent), var_offset (0) {}

        variable_symbol* get_variable(std::string name) {
            if (variables.count(name) == 1)
                return variables[name];
            if (parent == NULL)
                return nullptr;
            return parent->get_variable(name);
        }

        function_symbol* get_function(std::string name) {
            if (functions.count(name) == 1)
                return functions[name];
            if (parent == NULL)
                return nullptr;
            return parent->get_function(name);
        }

        bool try_declare(variable_symbol* v) {
            if (variables.count(v->name) == 1) {
                return false;
            }
            
            var_offset += 8;
            variables[v->name] = v;
            return true;
        }

        bool try_declare(function_symbol* f) {
            if (functions.count(f->name) == 1) {
                return false;
            }

            functions[f->name] = f;
            return true;
        }

        std::vector<variable_symbol*> get_all_variables() {
            std::vector<variable_symbol*> res;
            res.resize(variables.size());

            for (const auto& pair : variables) {
                res.push_back(pair.second);
            }

            if (parent) {
                auto p = parent->get_all_variables();
                for (const auto& pair : variables) {
                    res.push_back(pair.second);
                }
            }

            return res;
        }

        std::vector<function_symbol*> get_all_functions() {
            std::vector<function_symbol*> res;
            res.resize(functions.size());

            for (const auto& pair : functions) {
                res.push_back(pair.second);
            }

            if (parent) {
                auto p = parent->get_all_functions();
                for (const auto& pair : functions) {
                    res.push_back(pair.second);
                }
            }

            return res;
        }

        int get_total_offset() {
            int offset = var_offset;

            if (parent)
                offset += parent->get_total_offset();

            return offset;
        }
};

bound_scope* current_scope;

void scope_enter() {
    current_scope = new bound_scope(current_scope);
}

void scope_leave() {
    current_scope = current_scope->parent;
}