#pragma once

#include "external/glad/glad.h"

#include "engine/entity/topology.hpp"

#include "engine/model/vertex.hpp"

namespace engine::model {

class Mesh {
  public:
    void upload();

    void render(engine::entity::Topology topology);

    void add_vertex(Vertex &vertex);
    void add_vertex(float x, float y, float z);

    void add_index(GLuint index);

    template <std::size_t N> void add_indices(const GLuint (&indices)[N]) {
        this->_indices.insert(this->_indices.end(), std::begin(indices), std::end(indices));
    }

    std::vector<engine::model::Vertex> &get_vertices();

    std::vector<GLuint> &get_indices();

    unsigned long get_vertices_size();

    unsigned long get_indices_size();

  private:
    static inline constexpr unsigned int _POSITION_ATTRIBUTE = 0;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ibo;

    std::vector<engine::model::Vertex> _vertices;

    std::vector<GLuint> _indices;

    void draw_lines();

    void draw_triangles();
};

} // namespace engine::model
