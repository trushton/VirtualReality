#include <Engine.h>
#include <graphics.h>

Engine e;
cavr::input::InputMap input_map;

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
    // A button that is pressed on the keyboard from the x11 plugin
    input_map.button_map["exit"] = "keyboard[Escape]";

    // A wii remote button
    input_map.button_map["color"] = "vrpn[WiiMote0[3]]";

    // A wand that we want to follow based on some tracker -- we are tracing point 0
    input_map.sixdof_map["wand"] = "vrpn[WiiMote0[0]]";

    input_map.sixdof_map["head"] = "vrpn[ShortGlass[0]]";

    if (!cavr::System::init(argc, argv, &input_map)) {
    LOG(ERROR) << "Failed to initialize cavr.";
    return -1;
    }


    return e.run();
}
