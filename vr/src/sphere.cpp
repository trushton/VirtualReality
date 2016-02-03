
#include "sphere.h"

#include <cavr/gfx/renderer.h>

using namespace vr;

namespace {
    size_t sphereCount = 0;
}

Sphere::Sphere(float r, const std::string& n, cavr::gl::Program *prog)
    : Object3D(prog),
      NUM_SEGMENTS(30),
      radius(r)
{
    geometry = cavr::gfx::Shapes::solidSphere(NUM_SEGMENTS, radius);
    numTriangles = geometry.size();
    vbo = new cavr::gl::VBO(geometry);
    vao = new cavr::gl::VAO();

    vao->setAttribute(program->getAttribute("in_position"),
                     vbo,
                     4,
                     GL_FLOAT,
                     0,
                     0,
                     0);

    color.x = 1; // r
    color.y = 0; // g
    color.z = 0; // b

    uniforms.color = program->getUniform("color");
    uniforms.projection = program->getUniform("projection");
    uniforms.view = program->getUniform("view");
    uniforms.model = program->getUniform("model");

    sphereCount++;
    if(n == "") {
        name = std::string("Sphere") + std::to_string(sphereCount);
    }
    else {
        name = n;
    }
}

Sphere::~Sphere()
{
    sphereCount--;
}

void Sphere::update(UpdateFunc f) {
    Object3D::update(f);
}

void Sphere::render() {
    using cavr::math::mat4f;

    program->begin();
    vao->bind();

    glUniformMatrix4fv(uniforms.projection, 1, GL_FALSE, cavr::gfx::getProjection().v);
    glUniformMatrix4fv(uniforms.view, 1, GL_FALSE, cavr::gfx::getView().v);
    model = rotation * mat4f::translate(position.x, position.y, position.z) * mat4f::scale(scale);

    glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, model.v);

    glUniform3f(uniforms.color, color.x, color.y, color.z);

    glDrawArrays(GL_TRIANGLES, 0, numTriangles);

    glBindVertexArray(0);

    Object3D::render();
}
