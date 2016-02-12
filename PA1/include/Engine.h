#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>
#include <chrono>
#include <cavr/cavr.h>
#include <cavr/gfx/renderer.h>
#include <cavr/gfx/shapes.h>
#include <cavr/gfx/ray.h>
#include <cavr/gl/shader.h>
#include <cavr/gl/vao.h>
#include <cavr/gl/vbo.h>
#include <glog/logging.h>
#include <math.h>

//class Input;
class Graphics;

class Engine
{
public:
    Engine();
    ~Engine();

    void init();

    int run();
    void stop(int exit_code = 0);

    static Engine *getEngine();

    float tick();
    float dt;
    void update();
    void frame();

    //Input *input;
    Graphics *graphics;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
    bool clicked, rayColor, project, dirlight;


private:
    static Engine *currentEngine;
};

#endif // ENGINE_H
