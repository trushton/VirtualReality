// #include <cavr/cavr.h>
// #include <cavr/gfx/renderer.h>
// #include <cavr/gfx/shapes.h>
// #include <cavr/gfx/ray.h>
// #include <cavr/gl/shader.h>
// #include <cavr/gl/vao.h>
// #include <cavr/gl/vbo.h>
// #include <glog/logging.h>
// //#include <glm/glm.hpp>
// #include <math.h>
// #include "Model.h"
// #include "ds_geom_pass_tech.h"
//
// // Self make files
// //#include <Test.h>
//
// // Using IrrKlang for this example
// #include <irrKlang.h>
// using namespace irrklang;
//
// #pragma comment(lib, "irrKlang.lib")
// // IrrKlang
//
//
// // Context Data used for this example
// struct ContextData {
//   // Shader Programs
//   cavr::gl::Program* simple_program;
//   cavr::gl::Program* cube_program;
//
//   //custom Programs
//   DSGeomPassTech geomProgram;
//
//   // Uniforms
//   GLint color_uniform;
//   GLint projection_uniform;
//   GLint view_uniform;
//   GLint model_uniform;
//   GLint mvp_uniform;
//
//   // VBOs and
//   cavr::gl::VAO* sphere_vao;
//   cavr::gl::VBO* sphere_vbo;
//   cavr::gl::VAO* cube_vao;
//   cavr::gl::VBO* cube_vbo;
//   cavr::gl::VBO* pointer_vbo;
//   cavr::gl::VAO* pointer_vao;
//
//   size_t num_triangles_in_sphere;
//   size_t num_triangles_in_cube;
//   size_t num_triangles_in_pointer;
//
//   //models
//   Model tree;
//
//   // Rotating angle
//   float cube_angle;
//
//   // Lets add some sound library stuff here
//    ISoundEngine* engine;
//    ISound* music;
// };
//
// // Initialize our program
// void initContext() {
//   ContextData* cd = new ContextData();
//
//   //init geomProgram
//   cd->geomProgram.init();
//   //load models
//   cd->tree.loadModel("./bin/tree/tree.obj");
//
//   // Initialize some irrklang music
//   cd->engine = createIrrKlangDevice();
//   // cd->music = cd->engine->play3D("media/136608__thesoundcatcher__wind-in-small-forrest-01.wav",
//   //   vec3df(0,1,0), // Music source position
//   //   true, // play looped
//   //   false, //  start paused
//   //   true); //  enable sound--no-cache-dir
//
//   cd->simple_program = cavr::gl::Program::createSimple();
//
//   // Create a program using s--no-cache-dir ome custom code of ours
//   cd->cube_program = new cavr::gl::Program();
//
//   // custom shader initialization
//
//   cavr::gl::VertexShader* vs = cavr::gl::VertexShader::fromFile("shaders/shader.vert");
//   if (!vs) {
//     LOG(ERROR) << "Failed to load simple vertex shader";
//     cavr::System::shutdown();
//     return;
//   }
//
//   cavr::gl::FragmentShader* fs = cavr::gl::FragmentShader::fromFile("shaders/shader.frag");
//   if (!fs) {
//     LOG(ERROR) << "Failed to load simple fragment shader";
//     cavr::System::shutdown();
//     return;
//   }
//
//   cd->cube_program->addShader(vs);
//   cd->cube_program->addShader(fs);
//
//   cd->cube_program->bindFragDataLocation(0,"color");
//   cd->cube_angle = 0;
//   if(!cd->cube_program->link())
//   {
//     LOG(ERROR) << "Failed to link simple shader";
//     delete vs;
//     delete fs;
//     cavr::System::shutdown();
//     return;
//   }
//   delete vs;
//   delete fs;
//
//
//   cd->mvp_uniform = cd->cube_program->getUniform("mvp");
//
//   std::vector<cavr::math::vec4f> cubeTriangles = cavr::gfx::Shapes::wireCube();
//   cd->num_triangles_in_cube = cubeTriangles.size();
//
//   cd->cube_vbo = new cavr::gl::VBO(cubeTriangles,GL_STATIC_DRAW);
//   cd->cube_vao = new cavr::gl::VAO();
//   cd->cube_vao->setAttribute(cd->cube_program->getAttribute("pos"),
//     cd->cube_vbo,
//     4,
//     GL_FLOAT,
//     0,
//     0,
//     0);
//
//   cd->color_uniform = cd->simple_program->getUniform("color");
//   cd->projection_uniform = cd->simple_program->getUniform("projection");
//   cd->view_uniform = cd->simple_program->getUniform("view");
//   cd->model_uniform = cd->simple_program->getUniform("model");
//
//   // Simple shader shader vbo and vao initialization
//   std::vector<cavr::math::vec4f> sphere_vertices =
//     cavr::gfx::Shapes::solidSphere(30, 30);
//   cd->num_triangles_in_sphere = sphere_vertices.size();
//   cd->sphere_vbo = new cavr::gl::VBO(sphere_vertices);
//   cd->sphere_vao = new cavr::gl::VAO();
//   cd->sphere_vao->setAttribute(cd->simple_program->getAttribute("in_position"),
//                                cd->sphere_vbo,
//                                4,
//                                GL_FLOAT,
//                                0,
//                                0,
//                                0
// );
//
//   auto pointer_vertices = cavr::gfx::Shapes::solidCylinder(30, 20, 0.1);
//   cd->num_triangles_in_pointer = pointer_vertices.size();
//   cd->pointer_vbo = new cavr::gl::VBO(pointer_vertices, GL_STATIC_DRAW);
//   cd->pointer_vao = new cavr::gl::VAO();
//   cd->pointer_vao->setAttribute(cd->simple_program->getAttribute("in_position"),
//                                 cd->pointer_vbo,
//                                 4,
//                                 GL_FLOAT,
//                                 0,
//                                 0,
//                                 0);
//
//   // set context data
//   cavr::System::setContextData(cd);
// }
//
// // STOLEN
// bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
// {
//     float discr = b * b - 4 * a * c;
//     if (discr < 0) return false;
//     else if (discr == 0) x0 = x1 = - 0.5 * b / a;
//     else {
//         float q = (b > 0) ?
//             -0.5 * (b + sqrt(discr)) :
//             -0.5 * (b - sqrt(discr));
//         x0 = q / a;
//         x1 = c / q;
//     }
//     if (x0 > x1) std::swap(x0, x1);
//
//     return true;
// }
//
// bool solveRaycast(const cavr::gfx::Ray& ray, const cavr::math::vec3f& pos, float radius_sq) {
//   float t0, t1;
//
//   cavr::math::vec3f L = ray.origin() - pos;
//   float a = ray.direction().dot(ray.direction());
//   float b = 2 * ray.direction().dot(L);
//   float c = L.dot(L) - radius_sq;
//   if(!solveQuadratic(a, b, c, t0, t1)) return false;
//
//   if (t0 > t1) std::swap(t0, t1);
//
//   if (t0 < 0) {
//     t0 = t1; // if t0 is negative, let's use t1 instead
//     if (t0 < 0) return false; // both t0 and t1 are negative
//   }
//
//     return true;
// }
//
// void frame() {
//   ContextData* cd = (ContextData*)cavr::System::getContextData();
// }
//
// static bool itemSelected = false;
// void render() {
//   using cavr::math::mat4f;
//   glEnable(GL_CULL_FACE);
//   glCullFace(GL_BACK);
//
//   // get the context data
//   ContextData* cd = (ContextData*)cavr::System::getContextData();
//
//   // use the simple program
//   cd->simple_program->begin();
//   cd->sphere_vao->bind();
//   glUniformMatrix4fv(cd->projection_uniform, 1, GL_FALSE, cavr::gfx::getProjection().v);
//   glUniformMatrix4fv(cd->view_uniform, 1, GL_FALSE, cavr::gfx::getView().v);
//   static auto model = mat4f::translate(0, 1, 0) * mat4f::scale(0.1);
//   static auto cylinderModel = mat4f::translate(0,1,0) * mat4f::scale(0.1);
//   auto cubeModel = mat4f::translate(0,1,0) * mat4f::scale(0.1);
//   cd->simple_program->end();
//
//   //attempt to render tree model
//   cd->geomProgram.enable();
//   auto treeModel = mat4f::translate(0,1,1) * mat4f::scale(0.2);
//   auto mvp4 = (cavr::gfx::getProjection() * cavr::gfx::getView() * treeModel);
//   //glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, treeModel.v);
//   cd->geomProgram.set("gWVP", mvp4);
//   cd->geomProgram.set("gWorld", treeModel);
//   cd->geomProgram.set("gColorMap", 1);
//   cd->tree.renderModel();
//
//   cd->simple_program->begin();
//   cd->sphere_vao->bind();
//
//
//   // Check if a button has been pressed
//
//
//   // draw the sphere for the simple program
//   glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, model.v);
//   glDrawArrays(GL_TRIANGLES, 0, cd->num_triangles_in_sphere);
//   glBindVertexArray(0);
//   //cd->simple_program->end();
//
//   cd->pointer_vao->bind();
//
//   auto wand_sixdof = cavr::input::getSixDOF("wand");
//   auto pos = wand_sixdof->getPosition();
//   //auto angle = wand_sixdof->getDirection();
//   //model = mat4f::translate(pos.x,pos.y,pos.z) * mat4f::scale(0.1) * mat4f::look_at(pos, pos + wand_sixdof->getForward(), wand_sixdof->getUp()); //mat4f::rotate(3.14, wand_sixdof->getForward().cross(wand_sixdof->getUp()));
//
//   //RENDER z cylinder
//   cylinderModel =  mat4f::translate(0,0,0) * mat4f::rotate(1.57, cavr::math::vec3f(0,0,1))* mat4f::scale(0.1);
//   glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, cylinderModel.v);
//   glUniform3f(cd->color_uniform, 0, 0, 1);
//   glDrawArrays(GL_TRIANGLES, 0, cd->num_triangles_in_pointer);
//
//   //RENDER y CYLINDER
//   cylinderModel =  mat4f::translate(0,0,0) * mat4f::rotate(-1.57, cavr::math::vec3f(1,0,0))* mat4f::scale(0.1);
//   glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, cylinderModel.v);
//   glUniform3f(cd->color_uniform, 0, 1, 0);
//   glDrawArrays(GL_TRIANGLES, 0, cd->num_triangles_in_pointer);
//
//   //RENDER X CYLINDER
//   cylinderModel =  mat4f::translate(0,0,0) * mat4f::rotate(1.57, cavr::math::vec3f(0,1,0))* mat4f::scale(0.1);
//   glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, cylinderModel.v);
//   glUniform3f(cd->color_uniform, 1, 0, 0);
//   glDrawArrays(GL_TRIANGLES, 0, cd->num_triangles_in_pointer);
//
//   cylinderModel = wand_sixdof->getMatrix() * mat4f::translate(0, 0, -2) * mat4f::scale(0.1);
//   //cout << "POSITION: " << wand_sixdof->getPosition() << endl;
//   //cout << "DIRECTION: " << wand_sixdof->getForward() << endl;
//
//   glUniformMatrix4fv(cd->model_uniform, 1, GL_FALSE, cylinderModel.v);
//   glUniform3f(cd->color_uniform, 0, 1, 1);
//   glDrawArrays(GL_TRIANGLES, 0, cdvoid frame() {
//   ContextData* cd = (ContextData*)cavr::System::getContextData();
// }sixdof->getForward());
//      cavr::math::vec3f updatedPosition(model[3][0], model[3][1], model[3][2]);
//      if(solveRaycast(ray, updatedPosition, 0.075)) {
//        LOG(INFO) << "HIT";
//        model = wand_sixdof->getMatrix() * mat4f::translate(0, 0, -2) * mat4f::scale(0.1);
//        itemSelected = true;
//      }
//    }
//    else {
//       itemSelected = false;
//      }
//
//    if(itemSelected) {
//       glUniform3f(cd->color_uniform, 0, 0, 1);
//    }
//
//    else {
//      glUniform3f(cd->color_uniform, 1, 1, 0);
//    }
//
//   cd->simple_program->end();
//
//   // Cube Program
//   cd->cube_program->begin();
//   cd->cube_vao->bind();
//
//   // set cube angle
//   cd->cube_angle += 3.14/4.0 * cavr::input::InputManager::dt()*1000;
//
//   // Set your current
//   auto position = cavr::input::getSixDOF("head")->getPosition();
//   position.x *= 10;
//   position.z *= 10;
//
//
//   cd->engine->setListenerPosition(vec3df(position.x,position.y,position.z), // Listener's position
//   vec3df(0,0,1)); // What direction is the listener's facing directiion -- in this case we are always stareing forward..
//
//   // rotate cube
//   glUniformMatrix4fv(cd->mvp_uniform, 1, GL_FALSE, (cavr::gfx::getProjection() * cavr::gfx::getView() * cubeModel).v );
//
//   // draw cube
//   glDrawArrays(GL_LINES,0,cd->num_triangles_in_cube);
//
//   // rotate cube
//   cubeModel = mat4f::translate(1,1,0) * mat4f::scale(0.1);
//   glUniformMatrix4fv(cd->mvp_uniform, 1, GL_FALSE, (cavr::gfx::getProjection() * cavr::gfx::getView() * cubeModel).v );
//
//   // draw cube
//   glDrawArrays(GL_LINES,0,cd->num_triangles_in_cube);
//   glBindVertexArray(0);
//   cd->cube_program->end();
// }
//
// void destructContext() {
//   ContextData* cd = (ContextData*)cavr::System::getContextData();
//   delete cd;
// }
//
// void update() {void frame() {
//   ContextData* cd = (ContextData*)cavr::System::getContextData();
// }
//   // shutdown cavr..
//   if (cavr::input::getButton("exit")->delta() == cavr::input::Button::Pressed) {
//     cavr::System::shutdown();
//     return;
//   }
// }
//
// // int main(int argc, char** argv) {
// //
// //   //google::InitGoogleLogging(argv[0]);
// //   //Test *val = new Test();
// //   //LOG(INFO) << "Setting callbacks.";
// //
// //   // cavr is a system of callbacks
// //   cavr::System::setCallback("update", update);
// //   cavr::System::setCallback("init_gl_context", initContext);
// //   cavr::System::setCallback("update_gl_context", frame);
// //   cavr::System::setCallback("gl_render", render);
// //   cavr::System::setCallback("destruct_gl_context", destructContext);
// //   cavr::input::InputMap input_map;
// //
// //   // set input map for buttons,keyboard, and sixdofs
// //
// //   // A button that is pressed on the keyboard from the x11 plugin
// //   input_map.button_map["exit"] = "keyboard[Escape]";
// //
// //   // A wii remote button
// //   input_map.button_map["color"] = "vrpn[WiiMote0[3]]";
// //
// //   // A wand that we want to follow based on some tracker -- we are tracing point 0
// //   input_map.sixdof_map["wand"] = "vrpn[WiiMote0[0]]";
// //
// //   input_map.sixdof_map["head"] = "vrpn[ShortGlass[0]]";
// //
// //   if (!cavr::System::init(argc, argv, &input_map)) {
// //     LOG(ERROR) << "Failed to initialize cavr.";
// //     return -1;
// //   }
// //
// //   LOG(INFO) << "Successfully initialized cavr.";
// //   LOG(INFO) << "Callbacks set.";
// //   LOG(INFO) << "Starting simulation.";
// //
// //   // run cavr -- notice that this will be an infinite loop take a look at cavr::system.cpp
// //   cavr::System::run();
// //
// //   LOG(INFO) << "Shutting down.";
// //   return 0;
// // }
