/** https://www.songho.ca/opengl/gl_sphere.html */

#pragma once

#include <glm/glm.hpp>

#include "engine/entity/topology.hpp"

#include "engine/shader/shader.hpp"

#include "engine/model/mesh.hpp"

namespace engine::entity {

class Sphere {
  public:
    Sphere();

    Sphere(float x, float y, float z);

    void create();

    void render(engine::shader::Shader &shader);

  private:
    static inline constexpr float _RADIUS = 1.0f;

    static inline constexpr int _STACKS = 50;
    static inline constexpr int _SECTORS = 50;

    static inline constexpr engine::entity::Topology _TOPOLOGY = engine::entity::Topology::TRIANGLE;

    glm::vec3 _position;

    engine::model::Mesh _mesh;
};

} // namespace engine::entity
