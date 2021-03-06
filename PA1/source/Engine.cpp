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
    input_map.button_map["paint"] = "vrpn[WiiMote0[4]]";
    input_map.button_map["clear"] = "vrpn[WiiMote0[0]]";
    input_map.button_map["plus"] = "vrpn[WiiMote0[6]]";
    input_map.button_map["minus"] = "vrpn[WiiMote0[5]]";
    input_map.button_map["left"] = "vrpn[WiiMote0[7]]";
    input_map.button_map["right"] = "vrpn[WiiMote0[8]]";
    input_map.button_map["down"] = "vrpn[WiiMote0[9]]";
    input_map.button_map["up"] = "vrpn[WiiMote0[10]]";

    // button 1
    input_map.button_map["juan"] = "vrpn[WiiMote0[1]]";

    // A wand that we want to follow based on some tracker -- we are tracing point 0
    input_map.sixdof_map["wand"] = "vrpn[WiiMote0[0]]";

    input_map.sixdof_map["head"] = "vrpn[ShortGlasses[0]]";
    input_map.sixdof_map["emulated"] = "emulated";

    //controls for rotation, translation, and speed
    input_map.button_map["boost"] = "vrpn[WiiMote0[16]]";
    input_map.button_map["rotation"] = "vrpn[WiiMote0[17]]";

    // get input from the analog stick
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
