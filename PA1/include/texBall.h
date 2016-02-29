#ifndef TEXBALL_H
#define TEXBALL_H

#include <Vertex.h>
#include <camera.h>
#include <Model.h>
#include <ds_geom_pass_tech.h>


class texBall{
public:
  texBall(string mod, cavr::math::vec3f position);
  void init(cavr::math::vec3f position);
  void render(Camera* cam, DSGeomPassTech* geomProgram);
  void renderPainting(Camera* cam, DSGeomPassTech* geomProgram, cavr::math::mat4f camView);
  void setPos(cavr::math::vec3f newPos);
  cavr::math::vec3f getPos();

  //terrible protection of nothing
  string modelName;
  Model model;

private:
  cavr::math::vec3f position;

};


#endif
