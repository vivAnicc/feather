#pragma once
#include <vector>

class bound_node {
    public:
        virtual ~bound_node() {}
        virtual std::vector<bound_node*> get_children() = 0;
};