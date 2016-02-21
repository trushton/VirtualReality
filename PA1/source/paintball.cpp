#include <paintball.h>

Paintball::Paintball(cavr::math::vec3f color){
  //used for paintballs
  simple_program = cavr::gl::Program::createSimple();
  init(color);
}

void Paintball::init(cavr::math::vec3f color){
  // Simple shader shader vbo and vao initialization
  std::vector<cavr::math::vec4f> sphere_vertices = cavr::gfx::Shapes::solidSphere(30, 30);
  numTriangles = sphere_vertices.size();
  sphere_vbo = new cavr::gl::VBO(sphere_vertices);
  sphere_vao = new cavr::gl::VAO();
  sphere_vao->setAttribute(simple_program->getAttribute("in_position"),
                          sphere_vbo,
                          4,
                          GL_FLOAT,
                          0,
                          0,
                          0);

  color_uniform = simple_program->getUniform("color");
  projection_uniform = simple_program->getUniform("projection");
  view_uniform = simple_program->getUniform("view");
  model_uniform = simple_program->getUniform("model");
  setColor(color);
}

void Paintball::render(cavr::math::mat4f camView){
  simple_program->begin();
  sphere_vao->bind();
  glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, cavr::gfx::getProjection().v);
  glUniformMatrix4fv(view_uniform, 1, GL_FALSE, (cavr::gfx::getView()).v);
  model = cavr::math::mat4f::translate(pos) * cavr::math::mat4f::scale(0.2);

  // draw the sphere for the simple program
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.v);
  glUniform3f(color_uniform, color.x, color.y, color.z);
  glDrawArrays(GL_TRIANGLES, 0, numTriangles);
  glBindVertexArray(0);
  simple_program->end();
}


cavr::math::vec3f Paintball::getColor(){
  return color;
}

void Paintball::setColor(cavr::math::vec3f newColor){
  color = newColor;
}

cavr::math::vec3f Paintball::getPos(){
  return pos;
}

void Paintball::setPos(cavr::math::vec3f newPos){
  pos = newPos;
}
