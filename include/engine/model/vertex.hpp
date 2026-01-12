#pragma once

#include <glm/glm.hpp>

namespace engine::model {

struct Vertex {
    glm::vec3 position;

    Vertex() : Vertex(0.0f, 0.0f, 0.0f) {
    }

    Vertex(float x, float y, float z) : position(x, y, z) {
    }
};

} // namespace engine::model
