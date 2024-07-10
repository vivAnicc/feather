#pragma once
#include <typeinfo>
#include "binder.cpp"
#include "statement_binding.cpp"
#include "../symbols/pointer_symbol.cpp"

template<class T>
bound_expression* bind_expression(T* t);
std::optional<type_symbol*> string_to_type(const std::string& name);

template<class T>
type_symbol* bind_type(T* t) {
    if (t == NULL) {
        std::cerr << "Null node encountered!" << std::endl;
        return &type_error;
    }
    if (auto stmt = dynamic_cast<type_builtin*>(t)) {
        return bind_type(stmt);
    }
    else if (auto stmt = dynamic_cast<type_ident*>(t)) {
        return bind_type(stmt);
    }
    else if (auto stmt = dynamic_cast<type_deref*>(t)) {
        return bind_type(stmt);
    }
    else if (auto stmt = dynamic_cast<type_ptr*>(t)) {
        return bind_type(stmt);
    }
    else if (auto stmt = dynamic_cast<type_expr*>(t)) {
        return bind_type(stmt);
    }
    else {
        std::cerr << "Type node not recognized!    " << typeid(*t).name() << std::endl;
        return nullptr;
    }
}

template<>
type_symbol* bind_type(type_builtin* t) {
    auto string = std::get<std::string>(t->ident.value.value());
    return string_to_type(string).value();
}

template<>
type_symbol* bind_type(type_ident* t) {
    // TODO: custom types
    return nullptr;
}

template<>
type_symbol* bind_type(type_deref* t) {
    // TODO: types containing types
    return nullptr;
}

template<>
type_symbol* bind_type(type_ptr* t) {
    auto base = bind_type(t->base);
    return pointer(base);
}

template<>
type_symbol* bind_type(type_expr* t) {
    auto expr = bind_expression(t->expr);
    return expr->type;
}