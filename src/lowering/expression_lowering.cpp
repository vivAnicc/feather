#pragma once
#include "../binding/expression_binding.cpp"


template<class T>
bound_expression* lower_expression(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return new bound_expr_error;
    }
    if (auto stmt = dynamic_cast<bound_expr_error*>(t)) {
        std::cerr << "Error expression ecountered!" << std::endl;
        return { stmt };
        // return lower_expression(stmt);
    }
    else {
        return { t };
    }
}