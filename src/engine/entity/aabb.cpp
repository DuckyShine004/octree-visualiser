#include "engine/entity/aabb.hpp"

namespace engine::entity {

void AABB::render() {
    this->_mesh.render(this->_TOPOLOGY);
}

} // namespace engine::entity
