#include "engine/octree/node.hpp"

using namespace engine::entity;

namespace engine::octree {

Node::Node() : Node(0.0f, 0.0f, 0.0f, 0.0f) {
}

Node::Node(float x, float y, float z, float size) : _x(x), _y(y), _z(z), _size(size), _AABB(x, y, z, size), _is_leaf(false) {
}

void Node::add_sphere(Sphere &sphere) {
    this->_spheres.push_back(&sphere);
}

AABB &Node::get_AABB() {
    return this->_AABB;
}

std::vector<Sphere *> Node::get_spheres() {
    return this->_spheres;
}

void Node::set_is_leaf(bool is_leaf) {
    this->_is_leaf = is_leaf;
}

bool Node::is_leaf() {
    return this->_is_leaf;
}

} // namespace engine::octree
