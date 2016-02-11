#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>
//#include <glm/glm.hpp>
#include <cavr/cavr.h>
#include <cavr/gfx/renderer.h>
#include <cavr/gfx/shapes.h>
#include <cavr/gfx/ray.h>
#include <cavr/gl/shader.h>
#include <cavr/gl/vao.h>
#include <cavr/gl/vbo.h>
#include <glog/logging.h>
#include <math.h>

struct Vertex
    {
        GLfloat position[3];
        GLfloat normal[3];
        GLfloat texture[2];
    };

struct GLM_Vertex
{
    cavr::math::vec3f position;
    cavr::math::vec2f texture;
    cavr::math::vec3f normal;
    cavr::math::vec3f tangent;

    GLM_Vertex(){}

    GLM_Vertex(const cavr::math::vec3f pos, const cavr::math::vec2f uv, const cavr::math::vec3f norm, const cavr::math::vec3f tan){
        position = pos;
        texture = uv;
        normal = norm;
        tangent = tan;
    }
};

struct textureVertex
{
    GLfloat position[3];
    GLfloat uv[2];
};

#endif // VERTEX_H
