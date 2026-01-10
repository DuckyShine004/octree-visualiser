#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

#include "engine/octree/octree.hpp"

namespace engine::octree {

void Octree::construct() {
}

int Octree::get_size() {
    return Octree::_SIZE;
}

bool Octree::out_of_bounds(glm::vec3 &position) {
    float epsilon = glm::epsilon<float>();

    float lower = epsilon;
    float upper = Octree::_SIZE - epsilon;

    return position.x <= lower || position.x >= upper || position.y <= lower || position.y >= upper || position.z <= lower || position.z >= upper;
}

} // namespace engine::octree
