
#pragma once

#include <cavr/gl/shader.h>
#include <vector>
#include <string>

#include "object3d.h"

namespace vr {

typedef Object3D::ObjPtr ObjPtr;

class Scene : protected Object3D {
public:
    Scene();

    using Object3D::addChild;
    using Object3D::getChild;
    using Object3D::render;
    using Object3D::update;

    // void addChild(const ObjPtr&);
    // ObjPtr getChild(size_t);
    // ObjPtr getChild(const std::string&);

    static cavr::gl::Program* getDefaultProgram();

private:
    static cavr::gl::Program* defaultProgram;

    std::vector<ObjPtr> children;
};


} // namespace vr