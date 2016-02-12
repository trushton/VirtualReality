#include "Engine.h"
#include "graphics.h"
#include <Vertex.h>
//#define GLM_FORCE_RADIANS

//#include <glm/gtx/rotate_vector.hpp>

#include <fstream>


Graphics::Graphics(Engine *eng)
        : engine(eng)
{
    //camera = new Camera(engine);

}

Graphics::~Graphics()
{

}

void Graphics::init()
{
    initGL();
}

void Graphics::initGL()
{

    glClearColor(0.0, 0.0, 0.0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    //cube = new Cube();
    sim = new VRSim();

    //skybox = new Skybox();



}

void Graphics::tick(float dt)
{
    sim->tick(dt);
    render();
}

void Graphics::render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //updateView();
    //glClear(GL_DEPTH_BUFFER_BIT);
    sim->render();
}

void Graphics::stop()
{

}

// void Graphics::updateView()
// {
//     //view = camera->getView();
// }
//
// void Graphics::updateCamera()
// {
//
// }

// void Graphics::windowResized()
// {
//     // int width, height;
//     // getWindowSize(width, height);
//     // glViewport(0, 0, width, height);
//     // projection = glm::perspective(45.0f, //the FoV typically 90 degrees is good which is what this is set to
//     //                               float(width) /
//     //                               float(height), //Aspect Ratio, so Circles stay Circular
//     //                               0.9f, //Distance to the near plane, normally a small value like this
//     //                               1000000.0f); //Distance to the far plane,
// }

// void Graphics::getWindowSize(int &w, int &h) const
// {
//   //  SDL_GetWindowSize(window, &w, &h);
// }

Program *Graphics::getShaderProgram(const std::string &name) const
{
    return programs.at(name);
}

void Graphics::setClearColor(const cavr::math::vec3f &color)
{
    glClearColor(color[0], color[1], color[2], 1.0f);
}
