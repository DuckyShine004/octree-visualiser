#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "engine/entity/aabb.hpp"
#include "engine/entity/sphere.hpp"

#include "engine/octree/node.hpp"

namespace engine::octree {

class Octree {
  public:
    void construct(std::vector<engine::entity::Sphere> &spheres);

    std::vector<engine::entity::AABB> get_AABB();

    std::vector<engine::entity::Sphere *> query(engine::entity::Sphere &sphere);

    static int get_size();

    static bool out_of_bounds(glm::vec3 &position, float size);

  private:
    static inline constexpr int _SIZE = (1 << 4);

    static inline constexpr int _MAX_CAPACITY = 2;
    static inline constexpr int _MAX_DEPTH = 4;

    std::unique_ptr<engine::octree::Node> _root;

    /**
     * @brief: In XYZ order, e.g., LDB is Left-Down-Back, we'll use LDB as origin anchor
     *
     * Bottom:
     * (0,0,0) = LDB
     * (1,0,0) = RDB
     * (0,0,1) = LDF
     * (1,0,1) = RDF
     *
     * Top:
     * (0,1,0) = LUB
     * (1,1,0) = RUB
     * (0,1,1) = LUF
     * (1,1,1) = RUF
     *
     * @param spheres: the spheres (our entities)
     * @param x: x position of LDB
     * @param y: y position of LDB
     * @param z: z position of LDB
     * @param size: size of the encompassing node
     * @param depth: current traversed depth
     */
    std::unique_ptr<engine::octree::Node> construct(std::vector<engine::entity::Sphere> &spheres, float x, float y, float z, float size, int depth);
};

} // namespace engine::octree
