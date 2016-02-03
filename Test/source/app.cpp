#include <cavr/cavr.h>
#include <vr.h>
#include <glog/logging.h>
//#include <glm/glm.hpp>
#include <math.h>

// Self make files
#include <Test.h>

// Using IrrKlang for this example
#include <irrKlang.h>
using namespace irrklang;

// Initialize our program
void initContext() {
  auto scene = new vr::Scene();

  scene->addChild(new vr::Sphere(3.0f));
  // set context data
  cavr::System::setContextData(scene);
}

void frame() {
  auto scene = (vr::Scene*)cavr::System::getContextData();
}

void render() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  auto scene = (vr::Scene*) cavr::System::getContextData();

  scene->render();
  }

void destructContext() {
  auto scene = (vr::Scene*)cavr::System::getContextData();
  delete scene;
}

void update() {
  // shutdown cavr..
  if (cavr::input::getButton("exit")->delta() == cavr::input::Button::Pressed) {
    cavr::System::shutdown();
    return;
  }
}

int main(int argc, char** argv) {

  //google::InitGoogleLogging(argv[0]);
  //Test *val = new Test();
  //LOG(INFO) << "Setting callbacks.";

  // cavr is a system of callbacks
  cavr::System::setCallback("update", update);
  cavr::System::setCallback("init_gl_context", initContext);
  cavr::System::setCallback("update_gl_context", frame);
  cavr::System::setCallback("gl_render", render);
  cavr::System::setCallback("destruct_gl_context", destructContext);
  cavr::input::InputMap input_map;

  // set input map for buttons,keyboard, and sixdofs

  // A button that is pressed on the keyboard from the x11 plugin
  input_map.button_map["exit"] = "keyboard[Escape]";

  if (!cavr::System::init(argc, argv, &input_map)) {
    LOG(ERROR) << "Failed to initialize cavr.";
    return -1;
  }

  LOG(INFO) << "Successfully initialized cavr.";
  LOG(INFO) << "Callbacks set.";
  LOG(INFO) << "Starting simulation.";

  // run cavr -- notice that this will be an infinite loop take a look at cavr::system.cpp
  cavr::System::run();

  LOG(INFO) << "Shutting down.";
  return 0;
}
