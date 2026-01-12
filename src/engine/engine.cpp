#include "engine/engine.hpp"

#include "engine/entity/aabb.hpp"
#include "engine/octree/octree.hpp"

#include "manager/shader_manager.hpp"

#include "utility/math_utility.hpp"

using namespace engine::entity;

using namespace manager;

namespace engine {

void Engine::initialise() {
    this->_camera.update_projection();

    for (int i = 0; i < this->_NUMBER_OF_SPHERES; ++i) {
        float lower = 0.0f;
        float upper = octree::Octree::get_size();

        float x = utility::MathUtility::get_random_float(lower, upper);
        float y = utility::MathUtility::get_random_float(lower, upper);
        float z = utility::MathUtility::get_random_float(lower, upper);

        this->_spheres.push_back(Sphere{x, y, z});
    }
}

void Engine::update(GLFWwindow *window, float delta_time) {
    this->_camera.update(window, delta_time);

    for (Sphere &sphere : this->_spheres) {
        sphere.update(delta_time);
    }

    this->_octree.construct(this->_spheres);
    this->_AABBs = this->_octree.get_AABB();

    // TODO: Mark collisions (efficiently)
    for (Sphere &sphere : this->_spheres) {
        if (sphere.get_colliding()) {
            continue;
        }

        for (Sphere &other : this->_spheres) {
            if (&sphere == &other) {
                continue;
            }

            if (sphere.colliding(other)) {
                sphere.set_colliding(true);
                other.set_colliding(true);
            }
        }
    }
}

void Engine::render() {
    Shader &shader = ShaderManager::get_instance().get_shader("scene");

    shader.use();

    this->_camera.upload_model_view_projection(shader);

    for (Sphere &sphere : this->_spheres) {
        sphere.render(shader);
    }

    for (AABB &_AABB : this->_AABBs) {
        _AABB.render(shader);
    }
}

camera::Camera &Engine::get_camera() {
    return this->_camera;
}

} // namespace engine
