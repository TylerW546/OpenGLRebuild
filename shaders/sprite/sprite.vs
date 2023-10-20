#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 textureProjection;

void main()
{
    TexCoords = (textureProjection * vec4(vertex.z, vertex.w,1,1)).xy;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}