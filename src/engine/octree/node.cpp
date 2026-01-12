#include "engine/octree/node.hpp"

using namespace engine::entity;

namespace engine::octree {

Node::Node() : Node(0.0f, 0.0f, 0.0f, 0.0f) {
}

Node::Node(float x, float y, float z, float size) : _x(x), _y(y), _z(z), _size(size), _AABB(x, y, z, size) {
}

AABB &Node::get_AABB() {
    return this->_AABB;
}

} // namespace engine::octree
