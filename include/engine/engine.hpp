#pragma once

#include "engine/camera/camera.hpp"

#include "engine/entity/aabb.hpp"
#include "engine/entity/sphere.hpp"

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

    std::vector<engine::entity::Sphere> _spheres;

    engine::entity::AABB _aabb;
};

} // namespace engine
