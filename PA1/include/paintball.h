#ifndef PAINTBALL_H
#define PAINTBALL_H

#include <Vertex.h>
#include <Engine.h>

class Paintball{
public:
  Paintball(cavr::math::vec3f color);
  void init(cavr::math::vec3f color);
  void render(cavr::math::mat4f camView);
  void renderPainting(cavr::math::vec3f wandPos, cavr::math::mat4f camView, cavr::math::vec3f rotation);

  void setColor(cavr::math::vec3f newColor);
  cavr::math::vec3f getColor();

  void setPos(cavr::math::vec3f newPos);
  cavr::math::vec3f getPos();

private:
  cavr::math::mat4f model;


  //Taken from the app.cpp example
  size_t numTriangles;
  cavr::gl::VAO* sphere_vao;
  cavr::gl::VBO* sphere_vbo;

  //uniforms
  GLint color_uniform;
  GLint projection_uniform;
  GLint view_uniform;
  GLint model_uniform;
  GLint mvp_uniform;

  // ball color
  cavr::math::vec3f color;
  cavr::math::vec3f pos;

  cavr::gl::Program* simple_program;
};

#endif
