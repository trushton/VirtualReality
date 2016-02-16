#include <Engine.h>
#include <graphics.h>

Engine e;

class Graphics;

void update(){
  e.update();
}

void initContext(){
  e.graphics->init();
}

void frame(){
  e.frame();
}

void render(){
  e.dt = e.tick();
  e.graphics->tick(e.dt);
}

void stop(){
  e.stop();
}

int main(int argc, char **argv)
{

    // cavr is a system of callbacks
    cavr::System::setCallback("update", update);
    cavr::System::setCallback("init_gl_context", initContext);
    cavr::System::setCallback("update_gl_context", frame);
    cavr::System::setCallback("gl_render", render);
    cavr::System::setCallback("destruct_gl_context", stop);


    //input->init();


    if (!cavr::System::init(argc, argv, &e.input_map)) {
    LOG(ERROR) << "Failed to initialize cavr.";
    return -1;
    }


    return e.run();
}
