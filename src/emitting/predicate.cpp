#pragma once
#include <string>

enum class predicate : int {
    e,
    ne,
    l,
    nl,
    g,
    ng,
    le,
    nle,
    ge,
    nge,
    s,
    ns,
    z,
    nz,
};

std::string pred_str[] = {
    "e",
    "ne",
    "l",
    "nl",
    "g",
    "ng",
    "le",
    "nle",
    "ge",
    "nge",
    "s",
    "ns",
    "z",
    "nz",
};

const std::string pred_to_string(const predicate& pred) {
    return pred_str[int(pred)];
}