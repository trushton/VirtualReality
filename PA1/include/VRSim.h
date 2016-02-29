#ifndef VRSIM_H
#define VRSIM_H


//#include <glm/glm.hpp>
#include <GBuffer.h>
#include <Model.h>
#include <ds_geom_pass_tech.h>
#include <ds_dir_light_pass_tech.h>
#include <ds_point_light_pass_tech.h>
#include <Technique.h>
#include <Engine.h>
#include <graphics.h>
#include <lights.h>
#include <Terrain.h>
#include <paintball.h>
#include <camera.h>
#include <pointer.h>
#include <skybox.h>
#include <texBall.h>


// Using IrrKlang for this project
#include <irrKlang.h>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

class VRSim{
public:
  VRSim();
  ~VRSim();
  virtual void init();
  virtual void tick(float dt);
  virtual void render();

  void DSGeometryPass();
  void DSStencilPass(unsigned int PointLightIndex);
  void BeginLightPasses();
  void DSPointLightsPass(unsigned int PointLightIndex);

  static float CalcPointLightBSphere(const PointLight& Light);
  float CalcSpotLightBSphere(const SpotLight& Light);

  void DSDirectionalLightPass();
  void DSFinalPass();

  void InitLights();
  void InitColorPalette();
  void InitTexturePalette();
  void InitBoxPositions();
  void DSLightPass();

  bool solveQuadratic(const float a, const float b, const float c, float &x0, float &x1);
  bool solveRaycast(const cavr::gfx::Ray& ray, const cavr::math::vec3f& pos, float radius_sq);

  std::string ErrorString(GLenum error);
  cavr::math::vec3f playerPos;
  cavr::input::SixDOF* wand_sixdof;
  void processInput();
  bool tex;


//////////////STANDARD STUFF////////////////
  // Rotating angle
  float cube_angle;

  // Lets add some sound library stuff here
  ISoundEngine* engine;
  ISound* music;

   // Shader Programs
  cavr::gl::Program* simple_program;
  cavr::gl::Program* cube_program;

   // Uniforms
  GLint color_uniform;
  GLint projection_uniform;
  GLint view_uniform;
  GLint model_uniform;
  GLint mvp_uniform;

   // VBOs and
  cavr::gl::VAO* sphere_vao;
  cavr::gl::VBO* sphere_vbo;
  cavr::gl::VAO* cube_vao;
  cavr::gl::VBO* cube_vbo;
  cavr::gl::VBO* pointer_vbo;
  cavr::gl::VAO* pointer_vao;

  size_t num_triangles_in_sphere;
  size_t num_triangles_in_cube;
  size_t num_triangles_in_pointer;
///////////////////////////////////////////////

private:
  GBuffer m_gbuffer;
  Camera* cam;
  Skybox * skybox;

   //custom Programs
  DSGeomPassTech geomProgram;
  Technique m_nullTech;

  DSPointLightPassTech pointProgram;
  DSDirLightPassTech dirProgram;

  DirectionalLight m_dirLight;
  vector<PointLight> m_pointLight;

  //models
  Model tree, quad, sphere, pen;

  Terrain *terrain;

  std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
  int time;

  int windowWidth, windowHeight;

  // Used for person movement
  float xValOld, yValOld, speedMod;
  bool boost, rotation;

  //used for painting
  std::vector<Paintball> colorPalette;
  std::vector<Paintball> painting;
  cavr::math::vec3f currentColor;


  //for painting textures
  std::vector<texBall> selectedTexture;
  std::vector<texBall> texPainting;
  int TexSphere;

  Pointer cursor;

};


#endif
