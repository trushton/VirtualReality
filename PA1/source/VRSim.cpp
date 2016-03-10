#include <VRSim.h>

VRSim::VRSim(){
  init();
}

VRSim::~VRSim(){

}

void VRSim::init(){
  windowWidth = 1920;
  windowHeight = 1080;
  InitLights();
  InitColorPalette();
  InitTexturePalette();

  m_gbuffer.Init(windowWidth,windowHeight);
  geomProgram.init();

  //initialize point lights
  pointProgram.init();
  //pointProgram.SetPointLight(m_pointLight[0]);

  dirProgram.init();
  dirProgram.SetDirectionalLight(m_dirLight);

  //not sure what this is used for
  m_nullTech.init();

  //load models
  tree.loadModel("./bin/tree/tree.obj");
  quad.loadModel("./bin/quad.obj");
  sphere.loadModel("./bin/sphere.obj");
  pen.loadModel("./bin/objects/Pen.obj");


  // Terrain
  terrain = new Terrain(cavr::math::vec3f(100,30,100), "./bin/terrain/output.jpg");
  terrain->initialize();

  //the origins of time
  t2 = t1 = std::chrono::high_resolution_clock::now();
  time = 0;
  xValOld = 0.0f;
  yValOld = 0.0f;
  boost = rotation = false;

  cam = Engine::getEngine()->graphics->camera;
  currentColor = cavr::math::vec3f(1,0,0);

  cursor.init();
  skybox = new Skybox();
}

void VRSim::processInput(){
  // handle analog stick movement
  auto xAnalog = cavr::input::getAnalog("x");
  auto xVal = xAnalog->getValue();
  auto yAnalog = cavr::input::getAnalog("y");
  auto yVal = yAnalog->getValue();

  //determines if we paint with color or textures
  if(cavr::input::getButton("plus")->delta() != cavr::input::Button::Open){
    tex = false;
  }
  else if(cavr::input::getButton("minus")->delta() != cavr::input::Button::Open){
    tex = true;
  }

  if(cavr::input::getButton("right")->delta() != cavr::input::Button::Open){
    if(TexSphere +1 < selectedTexture.size()){
      TexSphere++;
      usleep(100000);
    }
  }
  else if(cavr::input::getButton("left")->delta() != cavr::input::Button::Open){
    if(TexSphere -1 >= 0){
      TexSphere--;
      usleep(100000);
    }
  }
  // cout << xVal << " | " << yVal << "\n";
  if (cavr::input::getButton("boost")->delta() != cavr::input::Button::Held) {
      speedMod = 5.0f;
  }
  else{
    speedMod = 2.0f;
  }

  if(abs(xVal) > 0.05 || abs(yVal) > 0.05) {
    if (cavr::input::getButton("rotation")->delta() == cavr::input::Button::Held) {
        Engine::getEngine()->graphics->camera->rotate(xVal, yVal);
    }
    else{
      //auto head = cavr::input::getSixDOF("head");
      cavr::math::vec3f look_dir = cam->ViewDir;
      cavr::math::vec3f move_dir = (cavr::math::vec3f(-xVal, 0, yVal));
      cam->Move(look_dir * (yVal/speedMod));
      cam->Move(cam->RightVector * (xVal/speedMod));
      //cam->StrafeRight(xVal);
      //cam->Move(move_dir);

      //Engine::getEngine()->graphics->camera->Move(move_dir);
    }
  }

  //do this for each color palette ball
  for(int i = 0; i < colorPalette.size(); i++){
    if(cavr::input::getButton("color")->delta() != cavr::input::Button::Open){
      cavr::gfx::Ray ray(wand_sixdof->getPosition(), wand_sixdof->getForward());
       if(solveRaycast(ray, colorPalette[i].getPos(), 0.075)) {
         currentColor = colorPalette[i].getColor();
       }
    }
  }

  if(cavr::input::getButton("clear")->delta() != cavr::input::Button::Open){
    painting.clear();
    texPainting.clear();
  }




  if(cavr::input::getButton("paint")->delta() != cavr::input::Button::Open){
    cavr::math::vec3f forward = wand_sixdof->getForward();
    cavr::math::mat4f tempMat = (/*cam->getView()**/ wand_sixdof->getMatrix() * cavr::math::mat4f::translate(cavr::math::vec3f(0,0,-2)));
    cavr::math::vec3f wf = cavr::math::vec3f(tempMat[2][0], tempMat[2][1], tempMat[2][2]);
    cavr::math::vec3f wp = cavr::math::vec3f(tempMat[3][0], tempMat[3][1], tempMat[3][2]);
    cavr::math::vec3f better  =  cam->getPos() + cam->ViewDir + cavr::math::vec3f(wf.x, wf.y, wf.z) +cavr::math::vec3f(-wp.x, wp.y, -wp.z) ;
    cavr::math::vec3f finalPos = cavr::math::vec3f(-tempMat[3][0]+playerPos.x, tempMat[3][1]+playerPos.y, -tempMat[3][2]+playerPos.z);
    if(!tex){
       Paintball temp(currentColor);
       temp.setPos(finalPos);
       //temp.setPos(better);

       painting.push_back(temp);
    }
    else{
      texBall temp(selectedTexture[TexSphere].modelName, finalPos);
      texPainting.push_back(temp);
    }
  }

  wand_sixdof = cavr::input::getSixDOF("wand");
  cursor.wandModel = (wand_sixdof->getMatrix() * cavr::math::mat4f::translate(0, 0, -2.5) * cavr::math::mat4f::scale(0.1));

  cursor.setColor(currentColor);
}

void VRSim::tick(float dt){
  playerPos = Engine::getEngine()->graphics->camera->getPos();
  auto headPosition = cavr::input::getSixDOF("head")->getPosition();
  auto emulated = cavr::input::getSixDOF("emulated");
  auto emulatedMatrix = emulated->getMatrix();
  emulatedMatrix[3].xyz = playerPos;
  emulated->setState(emulatedMatrix);

  tree.model = cavr::math::mat4f::translate(0,0,0);
  quad.model = cavr::math::mat4f::translate(0,0,0);
  sphere.model = cavr::math::mat4f::translate(0,0,0);
  processInput();

}

void VRSim::render(){
  m_gbuffer.StartFrame();

  // perform geometry pass
  DSGeometryPass();

  //fix this plz
  skybox->render(playerPos);

  //perform point light pass
  glEnable(GL_STENCIL_TEST);
  for (unsigned int i = 0 ; i < m_pointLight.size(); i++) {
    DSStencilPass(i);
    if(!Engine::getEngine()->dirlight){
        DSPointLightsPass(i);
    }
  }
  glDisable(GL_STENCIL_TEST);

  DSDirectionalLightPass();

  DSFinalPass();




  // Get the Error
  // auto error = glGetError();
  // if ( error != GL_NO_ERROR )
  // {
  //   string val = ErrorString( error );
  //   std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  // }

}

// std::string VRSim::ErrorString(GLenum error)
// {
//   if(error == GL_INVALID_ENUM)
//   {
//     return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
//   }
//
//   else if(error == GL_INVALID_VALUE)
//   {
//     return "GL_INVALID_VALUE: A numeric argument is out of range.";
//   }
//
//   else if(error == GL_INVALID_OPERATION)
//   {
//     return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
//   }
//
//   else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
//   {
//     return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
//   }
//
//   else if(error == GL_OUT_OF_MEMORY)
//   {
//     return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
//   }
//   else
//   {
//     return "None";
//   }
// }

void VRSim::DSGeometryPass(){
  m_gbuffer.BindForGeomPass();
  //geomProgram.enable();

  // Only the geometry pass updates the depth buffer

  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  //render the pointer

  cursor.render(cam->getView());

  //render each ball of the color palette
  if(!tex){
    for(int i = 0; i < colorPalette.size(); i++){
      colorPalette[i].render(cam->getView());
    }
  }
  //render the painting itself
  for(int i = 0; i < painting.size(); i++){
    painting[i].renderPainting(wand_sixdof->getPosition() + cavr::math::vec3f(0, 0, -2), cam->getView(), wand_sixdof->getForward());
  }



  //enable the terrains program and render it
  terrain->enable();
  terrain->model = cavr::math::mat4f::translate(cavr::math::vec3f(0 , -100 , 0));
  terrain->render(terrain->time);

  //enable geom program for those objects that require it
  geomProgram.enable();

  if(tex){
    selectedTexture[TexSphere].render(cam, &geomProgram);
  }

  for(int i = 0; i < texPainting.size(); i++){
    texPainting[i].renderPainting(cam, &geomProgram, cam->getView());
  }

  //load regular models

  /////loads one model/////
  wand_sixdof = cavr::input::getSixDOF("wand");
  pen.model = wand_sixdof->getMatrix()* cavr::math::mat4f::translate(cavr::math::vec3f(0,0,-1)) * cavr::math::mat4f::scale(0.1);
  //pen.model = cavr::math::mat4f::translate(cavr::math::vec3f(0,0,0)) * cavr::math::mat4f::scale(0.1) ;
  auto mvp4 = (cavr::gfx::getProjection() * (cavr::gfx::getView()) * pen.model );
  geomProgram.set("gWVP", mvp4);
  geomProgram.set("gWorld", pen.model);
  geomProgram.set("gColorMap", 0);
  pen.renderModel();
  /////////////////////////


  glDepthMask(GL_FALSE);
}

void VRSim::DSStencilPass(unsigned int PointLightIndex){
  m_nullTech.enable();

  // Disable color/depth write and enable stencil
  m_gbuffer.BindForStencilPass();
  glEnable(GL_DEPTH_TEST);

  glDisable(GL_CULL_FACE);

  glClear(GL_STENCIL_BUFFER_BIT);

  // We need the stencil test to be enabled but we want it
  // to succeed always. Only the depth test matters.
  glStencilFunc(GL_ALWAYS, 0, 0);

  glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
  glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

  float BSphereScale = CalcPointLightBSphere(m_pointLight[PointLightIndex]);
  sphere.model = cavr::math::mat4f::translate(m_pointLight[PointLightIndex].Position) * cavr::math::mat4f::scale(BSphereScale);

  auto mvp = (cavr::gfx::getProjection() * cavr::gfx::getView() * sphere.model);
  m_nullTech.set("gWVP", mvp);

  sphere.renderModel();
}

void VRSim::DSPointLightsPass(unsigned int PointLightIndex)
{
    m_gbuffer.BindForLightPass();
    pointProgram.enable();


    glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    float BSphereScale = CalcPointLightBSphere(m_pointLight[PointLightIndex]);
    sphere.model = cavr::math::mat4f::translate(m_pointLight[PointLightIndex].Position) * cavr::math::mat4f::scale(BSphereScale);

    auto mvp = (cavr::gfx::getProjection() * cavr::gfx::getView() * sphere.model);

    pointProgram.SetPointLight(m_pointLight[PointLightIndex]);
    pointProgram.set("gWVP", mvp);
    pointProgram.set("gEyeWorldPos", playerPos);
    pointProgram.set("gPositionMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    pointProgram.set("gColorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    pointProgram.set("gNormalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    pointProgram.set("gMatSpecularIntensity", 10.10f);
    pointProgram.set("gSpecularPower", 3.0f);


    glUniform2f(pointProgram.getLocation("gScreenSize"), (float) windowWidth, (float) windowHeight);

    sphere.renderModel();

    glCullFace(GL_BACK);
    glDisable(GL_BLEND);

}

float VRSim::CalcPointLightBSphere(const PointLight &Light){
  float MaxChannel = fmax(fmax(Light.Color.x, Light.Color.y), Light.Color.z);

  float ret = (-Light.Attenuation.Linear + sqrtf(Light.Attenuation.Linear * Light.Attenuation.Linear - 4 * Light.Attenuation.Exp * (Light.Attenuation.Exp - 256 * MaxChannel * Light.DiffuseIntensity)))
              /
              2 * Light.Attenuation.Exp;
  //return 1000;
  return 1000*ret;
}

void VRSim::DSDirectionalLightPass()
{
    m_gbuffer.BindForLightPass();
    dirProgram.enable();

    glDisable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);


    quad.model = cavr::math::mat4f::translate(0,0,0);
    dirProgram.SetDirectionalLight(m_dirLight);
    dirProgram.set("gWVP", quad.model);
    dirProgram.set("gPositionMap", GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    dirProgram.set("gColorMap", GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    dirProgram.set("gNormalMap", GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    dirProgram.set("gEyeWorldPos", playerPos);
    dirProgram.set("gMatSpecularIntensity", 0.10f);
    dirProgram.set("gSpecularPower", 32.0f);

    glUniform2f(dirProgram.getLocation("gScreenSize"), (float) windowWidth, (float) windowHeight);

    quad.renderModel();

    glDisable(GL_BLEND);
    glCullFace(GL_BACK);
}

void VRSim::DSFinalPass()
{
    m_gbuffer.BindForFinalPass();
    glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void VRSim::InitLights()
{
  m_dirLight.AmbientIntensity = 0.5f;
  m_dirLight.Color = COLOR_WHITE;
  m_dirLight.DiffuseIntensity = 0.25f;
  m_dirLight.Direction = cavr::math::vec3f(-1, -1, -1);

  PointLight temp;
  temp.DiffuseIntensity = 10.3f;
  temp.AmbientIntensity = 100.9f;
  temp.Color = COLOR_BLUE;
  temp.Position = cavr::math::vec3f(0,1,0);
  temp.Attenuation.Constant = .10f;
  temp.Attenuation.Linear = 0.1f;
  temp.Attenuation.Exp = .1f;
  m_pointLight.push_back(temp);

}

void VRSim::InitColorPalette(){
  Paintball temp(cavr::math::vec3f(1,0,0));

  temp.setPos(cavr::math::vec3f(1,-1,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,1,0));
  temp.setPos(cavr::math::vec3f(1,-.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,0,1));
  temp.setPos(cavr::math::vec3f(1,0,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,1,0));
  temp.setPos(cavr::math::vec3f(1,.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,1,1));
  temp.setPos(cavr::math::vec3f(1,1,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,0,1));
  temp.setPos(cavr::math::vec3f(1,1.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,1,1));
  temp.setPos(cavr::math::vec3f(1,2,-2));
  colorPalette.push_back(temp);


}

void VRSim::InitTexturePalette(){
  texBall temp("./bin/spheres/plane.obj", cavr::math::vec3f(-.5,0.5,-1));
  selectedTexture.push_back(temp);

  temp.modelName = "./bin/spheres/goo.obj";
  temp.model.loadModel(temp.modelName);
  selectedTexture.push_back(temp);

  tex = false;
  TexSphere = 0;
}

//STOLEN
bool VRSim::solveQuadratic(const float a, const float b, const float c, float &x0, float &x1){
  float discr = b * b - 4 * a * c;
  if (discr < 0) return false;
  else if (discr == 0) x0 = x1 = - 0.5 * b / a;
  else {
      float q = (b > 0) ?
          -0.5 * (b + sqrt(discr)) :
          -0.5 * (b - sqrt(discr));
      x0 = q / a;
      x1 = c / q;
  }
  if (x0 > x1) std::swap(x0, x1);

  return true;
}

bool VRSim::solveRaycast(const cavr::gfx::Ray& ray, const cavr::math::vec3f& pos, float radius_sq) {
  float t0, t1;

  cavr::math::vec3f L = ray.origin() - pos;
  float a = ray.direction().dot(ray.direction());
  float b = 2 * ray.direction().dot(L);
  float c = L.dot(L) - radius_sq;
  if(!solveQuadratic(a, b, c, t0, t1)) return false;

  if (t0 > t1) std::swap(t0, t1);

  if (t0 < 0) {
    t0 = t1; // if t0 is negative, let's use t1 instead
    if (t0 < 0) return false; // both t0 and t1 are negative
  }

    return true;
}
