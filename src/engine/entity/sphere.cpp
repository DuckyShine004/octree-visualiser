#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>

#include "engine/entity/sphere.hpp"

#include "engine/octree/octree.hpp"

#include "utility/math_utility.hpp"

#include "common/constant.hpp"

using namespace engine::shader;

using namespace engine::model;

using namespace common;

namespace engine::entity {

Sphere::Sphere() : Sphere(0.0f, 0.0f, 0.0f) {
}

Sphere::Sphere(float x, float y, float z) : _position(x, y, z), _colliding(false) {
    this->initialise();

    this->create();
}

void Sphere::initialise() {
    this->_direction = this->get_direction();
    this->_speed = this->get_speed();
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

void Sphere::update(float delta_time) {
    glm::vec3 velocity = delta_time * this->_speed * this->_direction;
    glm::vec3 next_position = this->_position + velocity;

    if (octree::Octree::out_of_bounds(next_position)) {
        this->_direction = this->get_direction();
        this->_speed = this->get_speed();
    }

    float octree_size = static_cast<float>(octree::Octree::get_size());

    if (next_position.z <= 0.0f || next_position.x >= octree_size) {
        this->_direction.x *= -1.0f;
    }

    if (next_position.y <= 0.0f || next_position.y >= octree_size) {
        this->_direction.y *= -1.0f;
    }

    if (next_position.z <= 0.0f || next_position.z >= octree_size) {
        this->_direction.z *= -1.0f;
    }

    next_position.x = glm::clamp(next_position.x, 0.0f, octree_size);
    next_position.y = glm::clamp(next_position.y, 0.0f, octree_size);
    next_position.z = glm::clamp(next_position.z, 0.0f, octree_size);

    this->_position = next_position;

    this->_colliding = false;
}

void Sphere::render(Shader &shader) {
    glm::mat4 model(1.0f);

    model = glm::translate(model, this->_position);
    model = glm::scale(model, glm::vec3(this->_RADIUS));

    shader.set_matrix4fv("u_model", model);

    if (this->_colliding) {
        shader.set_vector3f("u_colour", BLUE_RGB);
    } else {
        shader.set_vector3f("u_colour", WHITE_RGB);
    }

    this->_mesh.render(this->_TOPOLOGY);
}

glm::vec3 Sphere::get_direction() {
    glm::vec3 direction = utility::MathUtility::get_random_vector3f(glm::epsilon<float>(), 1.0f);

    if (utility::MathUtility::get_random_bool()) {
        direction.x *= -1.0f;
    }

    if (utility::MathUtility::get_random_bool()) {
        direction.y *= -1.0f;
    }

    if (utility::MathUtility::get_random_bool()) {
        direction.z *= -1.0f;
    }

    return glm::normalize(direction);
}

float Sphere::get_speed() {
    return utility::MathUtility::get_random_float(this->_SPEED_LIMIT.first, this->_SPEED_LIMIT.second);
}

bool Sphere::colliding(Sphere &other) {
    float distance = glm::distance(this->_position, other.get_position());

    return distance <= this->_RADIUS;
}

void Sphere::set_colliding(bool colliding) {
    this->_colliding = colliding;
}

glm::vec3 Sphere::get_position() {
    return this->_position;
}

} // namespace engine::entity
