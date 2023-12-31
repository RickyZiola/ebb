#ifndef BASIC_VERT_HPP
#define BASIC_VERT_HPP

#include <ebb/render/shader.hpp>

static const char * const _world_space_vert_src = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 objectMatrix;
uniform mat4 cameraMatrix;

mat3 getNormalMatrix(mat4 modelMatrix) {
    return mat3(transpose(inverse(modelMatrix)));
}

vec3 transformNormal(vec3 normal, mat4 modelMatrix) {
    mat3 normalMatrix = getNormalMatrix(modelMatrix);
    return normalize(normalMatrix * normal);
}

varying vec3 normal;
varying vec3 position;
void main() {
    gl_Position = (cameraMatrix * (objectMatrix * vec4(aPos, 1.0)));
    normal = transformNormal(aNorm, objectMatrix);
    position = (objectMatrix * vec4(aPos, 1.0)).xyz;
}
)";

// TODO: camera / projection matrices
namespace Ebb {

class WorldSpaceVertex : public VertexShader {
public:
    WorldSpaceVertex() : VertexShader(_world_space_vert_src) {}
private:

}; // end class WorldSpaceVertex
}; // end namespace Ebb

#endif // BASIC_VERT_HPP