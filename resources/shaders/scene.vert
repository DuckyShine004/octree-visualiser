#version 460 core

layout(location = 0) in vec3 v_position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_colour;

out vec3 f_colour;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(v_position, 1.0f);

    f_colour = u_colour;
}
