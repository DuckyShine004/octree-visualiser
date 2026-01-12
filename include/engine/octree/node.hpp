#pragma once

#include <memory>

#include "engine/entity/aabb.hpp"
#include "engine/entity/sphere.hpp"

namespace engine::octree {

class Node {
  public:
    Node();

    Node(float x, float y, float z, float size);

    void add_sphere(engine::entity::Sphere &sphere);

    engine::entity::AABB &get_AABB();

    std::vector<engine::entity::Sphere *> get_spheres();

    void set_is_leaf(bool is_leaf);

    bool is_leaf();

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

    bool _is_leaf;

    engine::entity::AABB _AABB;

    std::vector<engine::entity::Sphere *> _spheres;
};

} // namespace engine::octree
