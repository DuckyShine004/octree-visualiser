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

    void update(float delta_time);

    void render(engine::shader::Shader &shader);

    bool colliding(Sphere &other);

    glm::vec3 get_position();

    bool get_colliding();

    float get_radius();

    void set_colliding(bool colliding);

  private:
    static inline constexpr float _RADIUS = 1.0f;

    static inline constexpr int _STACKS = 50;
    static inline constexpr int _SECTORS = 50;

    static inline constexpr std::pair<float, float> _SPEED_LIMIT = {5.0f, 10.0f};

    static inline constexpr engine::entity::Topology _TOPOLOGY = engine::entity::Topology::TRIANGLE;

    glm::vec3 _position;
    glm::vec3 _direction;

    float _speed;

    bool _colliding;

    engine::model::Mesh _mesh;

    void initialise();

    void create();

    glm::vec3 get_direction();

    float get_speed();
};

} // namespace engine::entity
