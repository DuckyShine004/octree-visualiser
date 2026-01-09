#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "engine/entity/sphere.hpp"

using namespace engine::shader;

using namespace engine::model;

namespace engine::entity {

Sphere::Sphere() : Sphere(0.0f, 0.0f, 0.0f) {
}

Sphere::Sphere(float x, float y, float z) : _position(x, y, z) {
    this->create();
}

void Sphere::create() {
    float sector_step = glm::two_pi<float>() / this->_SECTORS;
    float stack_step = glm::pi<float>() / this->_STACKS;

    for (int stack_index = 0; stack_index <= this->_STACKS; ++stack_index) {
        float stack_angle = glm::half_pi<float>() - stack_index * stack_step;

        float xy = this->_RADIUS * cosf(stack_angle);
        float z = this->_RADIUS * sinf(stack_angle);

        for (int sector_index = 0; sector_index <= this->_SECTORS; ++sector_index) {
            float sector_angle = sector_index * sector_step;

            float x = xy * cosf(sector_angle);
            float y = xy * sinf(sector_angle);

            Vertex vertex;

            vertex.position = glm::vec3(x, y, z);

            this->_mesh.add_vertex(vertex);
        }
    }

    for (int stack_index = 0; stack_index < this->_STACKS; ++stack_index) {
        int k1 = stack_index * (this->_SECTORS + 1);
        int k2 = k1 + this->_SECTORS + 1;

        for (int sector_index = 0; sector_index < this->_SECTORS; ++sector_index, ++k1, ++k2) {
            if (stack_index != 0) {
                this->_mesh.add_index(k1);
                this->_mesh.add_index(k2);
                this->_mesh.add_index(k1 + 1);
            }

            if (stack_index != this->_STACKS - 1) {
                this->_mesh.add_index(k1 + 1);
                this->_mesh.add_index(k2);
                this->_mesh.add_index(k2 + 1);
            }
        }
    }

    this->_mesh.upload();
}

void Sphere::render(Shader &shader) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, this->_position);
    shader.set_matrix4fv("u_model", model);
    this->_mesh.render(this->_TOPOLOGY);
}

} // namespace engine::entity
