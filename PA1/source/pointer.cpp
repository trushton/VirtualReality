#include <pointer.h>

Pointer::Pointer(){
  //used for Pointers
  simple_program = cavr::gl::Program::createSimple();
}

void Pointer::init(){
  // Simple shader shader vbo and vao initialization
  std::vector<cavr::math::vec4f> pointer_vertices = cavr::gfx::Shapes::solidCylinder(30, 20, 0.1);
  numTriangles = pointer_vertices.size();
  pointer_vbo = new cavr::gl::VBO(pointer_vertices);
  pointer_vao = new cavr::gl::VAO();
  pointer_vao->setAttribute(simple_program->getAttribute("in_position"),
                          pointer_vbo,
                          4,
                          GL_FLOAT,
                          0,
                          0,
                          0);

  color_uniform = simple_program->getUniform("color");
  projection_uniform = simple_program->getUniform("projection");
  view_uniform = simple_program->getUniform("view");
  model_uniform = simple_program->getUniform("model");
  setColor(cavr::math::vec3f(1,0,0));
}

void Pointer::render(cavr::math::mat4f camView){
  simple_program->begin();
  pointer_vao->bind();
  glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, cavr::gfx::getProjection().v);
  glUniformMatrix4fv(view_uniform, 1, GL_FALSE, (cavr::gfx::getView()).v);
  model = wandModel;

  // draw the pointer for the simple program
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.v);
  glUniform3f(color_uniform, color.x, color.y, color.z);
  glDrawArrays(GL_TRIANGLES, 0, numTriangles);
  glBindVertexArray(0);
  simple_program->end();

}



cavr::math::vec3f Pointer::getColor(){
  return color;
}

void Pointer::setColor(cavr::math::vec3f newColor){
  color = newColor;
}

cavr::math::vec3f Pointer::getPos(){
  return pos;
}

void Pointer::setPos(cavr::math::vec3f newPos){
  pos = newPos;
}
