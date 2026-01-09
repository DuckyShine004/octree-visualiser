#version 460 core

#extension GL_ARB_bindless_texture : enable

layout(location = 0) in vec3 v_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(v_position, 1.0);
}
