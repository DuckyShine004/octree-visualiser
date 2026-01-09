#pragma once

#include "engine/entity/topology.hpp"

#include "engine/model/mesh.hpp"

namespace engine::entity {

class AABB {
  public:
    void render();

  private:
    static inline constexpr engine::entity::Topology _TOPOLOGY = engine::entity::Topology::LINE;

    engine::model::Mesh _mesh;
};

} // namespace engine::entity
