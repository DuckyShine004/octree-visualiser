#pragma once

#include <glm/glm.hpp>

namespace engine::octree {

class Octree {
  public:
    void construct();

    static int get_size();

    static bool out_of_bounds(glm::vec3 &position);

  private:
    static inline constexpr int _SIZE = (1 << 4);
};

} // namespace engine::octree
