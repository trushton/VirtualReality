
#pragma once

#include <cavr/gfx/shapes.h>

#include "object3d.h"

namespace vr {

class Sphere : public Object3D {
public:
    Sphere(float, const std::string& = "", cavr::gl::Program* = nullptr);
    ~Sphere();

    void update(UpdateFunc = UpdateFunc());
    void render();

private:
    const size_t NUM_SEGMENTS;
    float radius;
};

} // namespace vr
