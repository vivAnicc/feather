#pragma once
#include <map>
#include <ranges>
#include "../symbols/function_symbol.cpp"

class bound_scope {
    public:
        std::map<std::string, variable_symbol*> variables;
        std::map<std::string, function_symbol*> functions;
        bound_scope* parent;
        int var_size = 0;
        int temp_size = 0;
        int max_temp_size = 0;

        bound_scope(bound_scope* parent = nullptr) : parent (parent) {}

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
            
            var_size += v->type->size;
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

        bool is_owned(variable_symbol* var) {
            if (variables.count(var->name) == 1 && variables[var->name] == var)
                return true;
            return false;
        }

        int offset() {
            return var_size + max_temp_size;
        }

        int get_offset(variable_symbol* var) {
            bool owned = is_owned(var);

            if (owned)
                return var->offset;
            
            if (parent == NULL)
                return -1;

            if (parent->is_owned(var)) {
                // int parent_offset = parent->offset() - parent->get_offset(var) + var->type->size;
                int parent_offset = parent->offset() - parent->get_offset(var) + 8;
                return -parent_offset;
            }
            else {
                int parent_offset = parent->get_offset(var) + parent->offset();
                return -parent_offset;
            }
        }

        int get_total_offset() {
            int tot = offset();

            if (parent)
                tot += parent->get_total_offset();

            return tot;
        }

        void add_temp(int s) {
            temp_size += s;
            if (temp_size > max_temp_size)
                max_temp_size = temp_size;
        }
};

bound_scope* current_scope;

void scope_enter() {
    current_scope = new bound_scope(current_scope);
}

bound_scope* scope_leave() {
    auto current = current_scope;
    current_scope = current->parent;
    return current;
}

int get_temp_var(int size) {
    current_scope->add_temp(size);
    return current_scope->temp_size;
}

void remove_temp_var(int size) {
    current_scope->temp_size -= size;
}