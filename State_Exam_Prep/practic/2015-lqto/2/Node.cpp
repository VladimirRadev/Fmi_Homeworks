#include "Node.hpp"
Node::Node(const int& value,const std::vector<Node*>& children)
            :value(value),children(children){}