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

}

void VRSim::processInput(){
  // handle analog stick movement
  auto xAnalog = cavr::input::getAnalog("x");
  auto xVal = xAnalog->getValue();
  auto yAnalog = cavr::input::getAnalog("y");
  auto yVal = yAnalog->getValue();

  // cout << xVal << " | " << yVal << "\n";
  if (cavr::input::getButton("boost")->delta() != cavr::input::Button::Open) {
      std::cout << "Boost\n";
      boost = !boost;
  }


  if (boost){
    Engine::getEngine()->graphics->camera->movementSpeed = 1.2f;
  }
  else{
    Engine::getEngine()->graphics->camera->movementSpeed = 1.0f;
  }

  if (cavr::input::getButton("rotation")->delta() != cavr::input::Button::Open) {
    std::cout << "rotation\n";
      rotation = !rotation;
      usleep(80000);
  }

  if(abs(xVal) > 0.05 || abs(yVal) > 0.05) {
     if(rotation){
       Engine::getEngine()->graphics->camera->rotate(xVal, yVal);
     }
     else{
       auto wand = cavr::input::getSixDOF("wand");
       cavr::math::vec3f wand_dir = wand->getForward();
       cavr::math::vec3f move_dir = (cavr::math::vec3f(-xVal, 0, -yVal));
       //Engine::getEngine()->graphics->camera->Move(wand_dir * -yVal);
       Engine::getEngine()->graphics->camera->Move(move_dir);
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
  }

  if(cavr::input::getButton("paint")->delta() != cavr::input::Button::Open){
     Paintball temp(currentColor);
     temp.setPos(cavr::math::vec3f(wand_sixdof->getPosition() + cavr::math::vec3f(0,0,-2)));
     painting.push_back(temp);
  }

  wand_sixdof = cavr::input::getSixDOF("wand");
  cursor.wandModel = (wand_sixdof->getMatrix() * cavr::math::mat4f::translate(0, 0, -2) * cavr::math::mat4f::scale(0.1));
  cursor.setColor(currentColor);
  playerPos = Engine::getEngine()->graphics->camera->getPos();
}

void VRSim::tick(float dt){
  tree.model = cavr::math::mat4f::translate(0,0,0);
  quad.model = cavr::math::mat4f::translate(0,0,0);
  sphere.model = cavr::math::mat4f::translate(0,0,0);
  processInput();

}

void VRSim::render(){
  m_gbuffer.StartFrame();

  // perform geometry pass
  DSGeometryPass();
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

std::string VRSim::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

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
  for(int i = 0; i < colorPalette.size(); i++){
    colorPalette[i].render(cam->getView());
  }

  //render the painting itself
  for(int i = 0; i < painting.size(); i++){
    painting[i].renderPainting(cam->getView());
  }

  //enable the terrains program and render it
  terrain->enable();
  terrain->model = cavr::math::mat4f::translate(cavr::math::vec3f(0 , -100 , 0));
  terrain->render(terrain->time);

  //enable geom program for those objects that require it
  geomProgram.enable();

  //load regular models

  /////loads one model/////
  // wand_sixdof = cavr::input::getSixDOF("wand");
  // pen.model = wand_sixdof->getMatrix()* cavr::math::mat4f::translate(cavr::math::vec3f(0,0,-1)) * cavr::math::mat4f::scale(0.1);
  // //pen.model = cavr::math::mat4f::translate(cavr::math::vec3f(0,0,0)) * cavr::math::mat4f::scale(0.1) ;
  // auto mvp4 = (cavr::gfx::getProjection() * (cavr::gfx::getView()) * pen.model );
  // geomProgram.set("gWVP", mvp4);
  // geomProgram.set("gWorld", pen.model);
  // geomProgram.set("gColorMap", 0);
  // pen.renderModel();
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
  m_dirLight.AmbientIntensity = 0.2f;
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

  temp.setPos(cavr::math::vec3f(1,1,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,1,0));
  temp.setPos(cavr::math::vec3f(1,2,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,0,1));
  temp.setPos(cavr::math::vec3f(1,3,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,1,0));
  temp.setPos(cavr::math::vec3f(1,2.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(0,1,1));
  temp.setPos(cavr::math::vec3f(1,3.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,0,1));
  temp.setPos(cavr::math::vec3f(1,1.5,-2));
  colorPalette.push_back(temp);

  temp.setColor(cavr::math::vec3f(1,1,1));
  temp.setPos(cavr::math::vec3f(1,4,-2));
  colorPalette.push_back(temp);


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
