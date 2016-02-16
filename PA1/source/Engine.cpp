//#include "input.h"
#include "graphics.h"
#include "Engine.h"
#include <chrono>
#include <iostream>


Engine *Engine::currentEngine = nullptr;

Engine::Engine()
{
    Engine::currentEngine = this;
    init();
}

Engine::~Engine()
{
    stop();
}

void Engine::init()
{

    // rayColor = false;
    // project = false;
    dirlight = true;
    //input = new Input(this);
    graphics = new Graphics(this);

    // A button that is pressed on the keyboard from the x11 plugin
    input_map.button_map["exit"] = "keyboard[Escape]";

    // A wii remote button
    input_map.button_map["color"] = "vrpn[WiiMote0[3]]";

    // A wand that we want to follow based on some tracker -- we are tracing point 0
    input_map.sixdof_map["wand"] = "vrpn[WiiMote0[0]]";

    input_map.sixdof_map["head"] = "vrpn[ShortGlass[0]]";

    input_map.analog_map["x"] = "vrpn[WiiMote0[21]]";
    input_map.analog_map["y"] = "vrpn[WiiMote0[22]]";

}

void Engine::update(){
  dt = tick();
  if (cavr::input::getButton("exit")->delta() == cavr::input::Button::Pressed) {
    cavr::System::shutdown();
    return;
  }
}

void Engine::frame(){
  graphics->sim = (VRSim*)cavr::System::getContextData();
}

int Engine::run()
{
    float dt;
    t1 = std::chrono::high_resolution_clock::now();

    cavr::System::run();

    return 0;
}

void Engine::stop(int exit_code)
{
    //input->stop();
    graphics->stop();

    //delete input;
    delete graphics;


    exit(exit_code);
}


Engine *Engine::getEngine()
{
    return currentEngine;
}


float Engine::tick()
{
    float dt;

    t2 = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration_cast<std::chrono::duration<float> >(t2 - t1).count();
    t1 = t2;

    return dt;
}
