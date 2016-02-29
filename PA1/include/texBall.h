#ifndef TEXBALL_H
#define TEXBALL_H

#include <Vertex.h>
#include <camera.h>
#include <Model.h>
#include <ds_geom_pass_tech.h>


class texBall{
public:
  texBall();
  void init();
  void render(Camera* cam, DSGeomPassTech* geomProgram);
  void renderPainting(cavr::math::vec3f wandPos, cavr::math::mat4f camView, cavr::math::vec3f rotation);


  void setPos(int index, cavr::math::vec3f newPos);
  cavr::math::vec3f getPos(int index);
  int currentModel;

private:
  std::vector<Model> types;
  std::vector<Model> painting;
  std::vector<cavr::math::vec3f> positions;
};


#endif
