#include <texBall.h>

texBall::texBall(){

}

void texBall::init(){
  Model temp;
  cavr::math::vec3f tempPos;

  temp.loadModel("./bin/spheres/iron.obj");
  tempPos = cavr::math::vec3f(-0.5,0,-1);
  types.push_back(temp);
  positions.push_back(tempPos);

  temp.loadModel("./bin/spheres/goo.obj");
  tempPos = cavr::math::vec3f(-0.5,0.5,-1);
  types.push_back(temp);
  positions.push_back(tempPos);
}

void texBall::render(Camera* cam, DSGeomPassTech* geomProgram){
  types[currentModel].model = cavr::math::mat4f::translate(positions[currentModel]) * cavr::math::mat4f::scale(0.1);
  auto mvp4 = (cavr::gfx::getProjection() * (cavr::gfx::getView()) * types[currentModel].model );
  geomProgram->set("gWVP", mvp4);
  geomProgram->set("gWorld", types[currentModel].model);
  geomProgram->set("gColorMap", 0);
  types[currentModel].renderModel();

}

void texBall::renderPainting(cavr::math::vec3f wandPos, cavr::math::mat4f camView, cavr::math::vec3f rotation){

}


cavr::math::vec3f texBall::getPos(int index){
  return positions[index];
}

void texBall::setPos(int index, cavr::math::vec3f newPos){
  positions[index] = newPos;
}
