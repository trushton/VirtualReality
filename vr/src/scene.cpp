
#include "scene.h"

using namespace vr;

cavr::gl::Program* Scene::defaultProgram = nullptr;

Scene::Scene()
{
}
// void Scene::addChild(const ObjPtr& obj) {
//     children.push_back(obj);
// }

// ObjPtr Scene::getChild(size_t index) {
//     return children.at(index);
// }

// ObjPtr Scene::getChild(const std::string& name) {
//     ObjPtr ptr = nullptr;
//     for(auto child : children) {
//         if(child->getName() == name) {
//             ptr = child;
//             break;
//         }
//     }

//     return ptr;
// }

cavr::gl::Program* Scene::getDefaultProgram() {
    if(!defaultProgram) {
        defaultProgram = cavr::gl::Program::createSimple();
    }
    return defaultProgram;
}