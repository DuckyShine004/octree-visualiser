#include "engine/engine.hpp"

#include "manager/shader_manager.hpp"

#include "logger/logger_macros.hpp"

using namespace engine::entity;

using namespace manager;

namespace engine {

void Engine::initialise() {
    this->_camera.update_projection();

    for (int i = 0; i < this->_NUMBER_OF_SPHERES; ++i) {
        float position = (float)i;
        this->_spheres.push_back(Sphere{position, position, position});
    }

    // this->_aabb
}

void Engine::update(GLFWwindow *window, float delta_time) {
    this->_camera.update(window, delta_time);

    // TODO: Update entity positions
    for (Sphere &sphere : this->_spheres) {
        sphere.update(delta_time);
    }
    // TODO: Construct quadtree
    // TODO: Mark colliding entities
}

void Engine::render() {
    Shader &shader = ShaderManager::get_instance().get_shader("sphere");
    shader.use();
    this->_camera.upload_model_view_projection(shader);
    for (Sphere &sphere : this->_spheres) {
        sphere.render(shader);
    }

    // this->_aabb.render();
}

camera::Camera &Engine::get_camera() {
    return this->_camera;
}

} // namespace engine
