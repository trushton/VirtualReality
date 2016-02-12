#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

//#include <glm/glm.hpp>
//#include "cube.h"
//#include "skybox.h"
//#include "camera.h"
//#include "water.h"
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <VRSim.h>

class Engine;
//class Camera;
class Texture;
class Program;
class VRSim;

class Graphics {
public:
    Graphics(Engine *eng);
    ~Graphics();

    void init();
    void tick(float dt);
    void render();
    void stop();

    //void updateView();
    //void updateCamera();
    //void windowResized();

    Program* getShaderProgram(const std::string& name) const;

    void setClearColor(const cavr::math::vec3f& color);

    cavr::math::mat4f view, projection;

    //Camera * camera;
    VRSim *sim;


private:
    void initGL();

    Engine *engine;
    std::map<std::string, Program*> programs;

    //Skybox * skybox;

};

#endif // GRAPHICS_HPP
