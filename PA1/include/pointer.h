#ifndef POINTER_H
#define POINTER_H

#include <Vertex.h>
#include <Engine.h>

class Pointer{
public:
  Pointer();
  void init();
  void render(cavr::math::mat4f camView);

  void setColor(cavr::math::vec3f newColor);
  cavr::math::vec3f getColor();
  void setPos(cavr::math::vec3f newPos);
  cavr::math::vec3f getPos();
  cavr::math::mat4f wandModel;

private:
  cavr::math::mat4f model;


  //Taken from the app.cpp example
  size_t numTriangles;
  cavr::gl::VAO* pointer_vao;
  cavr::gl::VBO* pointer_vbo;

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
