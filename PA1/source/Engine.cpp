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

}

void Engine::update(){
  dt = tick();
  if (cavr::input::getButton("exit")->delta() == cavr::input::Button::Pressed) {
    cavr::System::shutdown();
    return;
  }
}

void Engine::frame(){
  VRSim* sim = (VRSim*)cavr::System::getContextData();
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
