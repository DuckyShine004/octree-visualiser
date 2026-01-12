#pragma once

#include "engine/camera/camera.hpp"

#include "engine/entity/aabb.hpp"
#include "engine/entity/sphere.hpp"

#include "engine/octree/octree.hpp"

namespace engine {

class Engine {
  public:
    void initialise();

    void update(GLFWwindow *window, float delta_time);

    void render();

    camera::Camera &get_camera();

  private:
    static inline constexpr int _NUMBER_OF_SPHERES = 10;

    camera::Camera _camera;

    engine::octree::Octree _octree;

    std::vector<engine::entity::Sphere> _spheres;

    std::vector<engine::entity::AABB> _AABBs;
};

} // namespace engine
