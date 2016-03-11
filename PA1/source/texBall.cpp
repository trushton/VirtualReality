#include <texBall.h>

texBall::texBall(string mod, cavr::math::vec3f position){
  modelName = mod;
  init(position);
}

void texBall::init(cavr::math::vec3f position){
  model.loadModel(modelName);
  setPos(position);
}

void texBall::render(Camera* cam, DSGeomPassTech* geomProgram){
  model.model = cavr::math::mat4f::translate(palettePos) * cavr::math::mat4f::scale(0.1);
  auto mvp4 = (cavr::gfx::getProjection() * (cavr::gfx::getView()) * model.model );
  geomProgram->set("gWVP", mvp4);
  geomProgram->set("gWorld", model.model);
  geomProgram->set("gColorMap", 0);
  model.renderModel();

}

void texBall::renderPainting(Camera* cam, DSGeomPassTech* geomProgram, cavr::math::mat4f camView){
  for (int i = 0; i < positions.size(); i++){
    model.model = cavr::math::mat4f::translate(positions[i]) * cavr::math::mat4f::scale(0.1);
    auto mvp4 = (cavr::gfx::getProjection() * (cavr::gfx::getView() * camView) * model.model );
    geomProgram->set("gWVP", mvp4);
    geomProgram->set("gWorld", model.model);
    geomProgram->set("gColorMap", 0);
    model.renderModel();
  }
}

cavr::math::vec3f texBall::getPos(){
  return palettePos;
}

void texBall::setPos(cavr::math::vec3f newPos){
  palettePos = newPos;
}
