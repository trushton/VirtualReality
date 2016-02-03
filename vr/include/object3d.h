
#pragma once

#include <cavr/cavr.h>
#include <cavr/gl/shader.h>
#include <cavr/gl/vao.h>
#include <cavr/gl/vbo.h>

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace vr {

typedef std::function<void()> UpdateFunc;

class Object3D {
    public:
    typedef std::shared_ptr<Object3D> ObjPtr;

    Object3D(cavr::gl::Program* = nullptr);
    Object3D(const Object3D&) = default;
    Object3D(Object3D&&) = default;

    virtual ~Object3D();

    virtual void update(UpdateFunc = UpdateFunc());
    virtual void render();

    void addChild(Object3D*);
    void addChild(const ObjPtr&);
    ObjPtr getChild(size_t) const;
    ObjPtr getChild(const std::string&) const;
    const std::vector<ObjPtr>& getChildren() const;

    void setName(const std::string&);
    const std::string& getName() const;

    void setPosition(const cavr::math::vec3f&);
    const cavr::math::vec3f& getPosition() const;

    void setScale(float);
    float getScale() const;

    void setColor(const cavr::math::vec3f&);
    const cavr::math::vec3f& getColor() const;

    void setRotation(float, const cavr::math::vec3f&);
    const cavr::math::mat4f& getRotation() const;
    void setRotationTo(const Object3D&);

    protected:
    std::vector<ObjPtr> children;
    std::string name;

    // OpenGL Related Structures
    cavr::gl::Program *program;
    cavr::gl::VAO *vao;
    cavr::gl::VBO *vbo;

    struct {
        GLint color;
        GLint projection;
        GLint view;
        GLint model;
        GLint mvp;
    } uniforms;

    size_t numTriangles;

    std::vector<cavr::math::vec4f> geometry;
    cavr::math::vec3f position;
    float scale;

    cavr::math::mat4f model;
    cavr::math::mat4f rotation;

    cavr::math::vec3f color;
};

} // namespace vr
