#include <queue>

#include "engine/octree/octree.hpp"

using namespace engine::entity;

namespace engine::octree {

void Octree::construct(std::vector<Sphere> &spheres) {
    this->_root = this->construct(spheres, 0.0f, 0.0f, 0.0f, this->_SIZE, 0);
}

std::unique_ptr<Node> Octree::construct(std::vector<Sphere> &spheres, float x, float y, float z, float size, int depth) {
    if (depth == this->_MAX_DEPTH) {
        return nullptr;
    }

    std::unique_ptr<Node> node = std::make_unique<Node>(x, y, z, size);

    int capacity = 0;

    for (Sphere &sphere : spheres) {
        if (node->get_AABB().collide(sphere)) {
            node->add_sphere(sphere);
            ++capacity;
        }
    }

    float half_size = size / 2.0f;

    if (capacity <= this->_MAX_CAPACITY) {
        node->set_is_leaf(true);
        return node;
    }

    node->LDB = this->construct(spheres, x, y, z, half_size, depth + 1);
    node->RDB = this->construct(spheres, x + half_size, y, z, half_size, depth + 1);
    node->LDF = this->construct(spheres, x, y, z + half_size, half_size, depth + 1);
    node->RDF = this->construct(spheres, x + half_size, y, z + half_size, half_size, depth + 1);

    node->LUB = this->construct(spheres, x, y + half_size, z, half_size, depth + 1);
    node->RUB = this->construct(spheres, x + half_size, y + half_size, z, half_size, depth + 1);
    node->LUF = this->construct(spheres, x, y + half_size, z + half_size, half_size, depth + 1);
    node->RUF = this->construct(spheres, x + half_size, y + half_size, z + half_size, half_size, depth + 1);

    return node;
}

std::vector<Sphere *> Octree::query(Sphere &sphere) {
    Node *node = this->_root.get();

    if (node == nullptr) {
        return {};
    }

    while (!node->is_leaf()) {
        if (node->LDB != nullptr && node->LDB->get_AABB().collide(sphere)) {
            node = node->LDB.get();
        } else if (node->RDB != nullptr && node->RDB->get_AABB().collide(sphere)) {
            node = node->RDB.get();
        } else if (node->LDF != nullptr && node->LDF->get_AABB().collide(sphere)) {
            node = node->LDF.get();
        } else if (node->RDF != nullptr && node->RDF->get_AABB().collide(sphere)) {
            node = node->RDF.get();
        } else if (node->LUB != nullptr && node->LUB->get_AABB().collide(sphere)) {
            node = node->LUB.get();
        } else if (node->RUB != nullptr && node->RUB->get_AABB().collide(sphere)) {
            node = node->RUB.get();
        } else if (node->LUF != nullptr && node->LUF->get_AABB().collide(sphere)) {
            node = node->LUF.get();
        } else if (node->RUF != nullptr && node->RUF->get_AABB().collide(sphere)) {
            node = node->RUF.get();
        } else {
            break;
        }
    }

    return node->get_spheres();
}

std::vector<AABB> Octree::get_AABB() {
    std::vector<AABB> _aabb;

    if (this->_root == nullptr) {
        return _aabb;
    }

    std::queue<Node *> _queue;

    _queue.push(this->_root.get());

    while (!_queue.empty()) {
        Node *node = _queue.front();

        _queue.pop();

        if (node == nullptr) {
            continue;
        }

        _aabb.push_back(node->get_AABB());

        _queue.push(node->LDB.get());
        _queue.push(node->RDB.get());
        _queue.push(node->LDF.get());
        _queue.push(node->RDF.get());

        _queue.push(node->LUB.get());
        _queue.push(node->RUB.get());
        _queue.push(node->LUF.get());
        _queue.push(node->RUF.get());
    }

    return _aabb;
}

int Octree::get_size() {
    return Octree::_SIZE;
}

bool Octree::out_of_bounds(glm::vec3 &position, float size) {
    float lower = size;
    float upper = Octree::_SIZE - size;

    return position.x <= lower || position.x >= upper || position.y <= lower || position.y >= upper || position.z <= lower || position.z >= upper;
}

} // namespace engine::octree
