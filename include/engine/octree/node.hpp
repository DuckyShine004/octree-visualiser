#pragma once

#include <memory>

#include "engine/entity/aabb.hpp"

namespace engine::octree {

class Node {
  public:
    Node();

    Node(float x, float y, float z, float size);

    engine::entity::AABB &get_AABB();

    std::unique_ptr<Node> LDB;
    std::unique_ptr<Node> RDB;
    std::unique_ptr<Node> LDF;
    std::unique_ptr<Node> RDF;

    std::unique_ptr<Node> LUB;
    std::unique_ptr<Node> RUB;
    std::unique_ptr<Node> LUF;
    std::unique_ptr<Node> RUF;

  private:
    float _x;
    float _y;
    float _z;

    float _size;

    engine::entity::AABB _AABB;
};

} // namespace engine::octree
