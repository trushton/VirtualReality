
#include "object3d.h"
#include "scene.h"

#include <cmath>

#include <glog/logging.h>

using namespace vr;

Object3D::Object3D(cavr::gl::Program *prog)
    : program(prog),
      position(0,0,0),
      scale(1.0f),
      model(1),
      rotation(1)
{
    if(!prog) {
        LOG(INFO) << "Program is null, creating default";
        prog = Scene::getDefaultProgram();
    }
}

Object3D::~Object3D()
{
}

void Object3D::update(UpdateFunc f) {
    if(f) {
        f();
    }

    for(auto child : children) {
        child->update();
    }
}

void Object3D::render() {
    for(auto child : children) {
        child->render();
    }
}

void Object3D::addChild(Object3D *ptr) {
    ObjPtr obj(ptr);
    addChild(obj);
}

void Object3D::addChild(const ObjPtr& child) {
    children.push_back(child);
}

Object3D::ObjPtr Object3D::getChild(size_t index) const {
    return children.at(index);
}

Object3D::ObjPtr Object3D::getChild(const std::string& objName) const {
    ObjPtr ptr;
    for(const auto& child : children) {
        if(child->getName() == objName) {
            ptr = child;
            break;
        }
    }

    return ptr;
}

const std::vector<Object3D::ObjPtr>& Object3D::getChildren() const {
    return children;
}

void Object3D::setName(const std::string& newName) {
    name = newName;
}

const std::string& Object3D::getName() const {
    return name;
}

void Object3D::setPosition(const cavr::math::vec3f& newPos) {
    position = newPos;
}

const cavr::math::vec3f& Object3D::getPosition() const {
    return position;
}

void Object3D::setScale(float newScale) {
    scale = newScale;
}

float Object3D::getScale() const {
    return scale;
}

void Object3D::setColor(const cavr::math::vec3f& newColor) {
    color = newColor;
}

const cavr::math::vec3f& Object3D::getColor() const {
    return color;
}

void Object3D::setRotation(float angle, const cavr::math::vec3f& axis) {
    rotation = cavr::math::mat4f::rotate(angle, axis);
}

const cavr::math::mat4f& Object3D::getRotation() const {
    return rotation;
}

void Object3D::setRotationTo(const Object3D& obj) {
    auto direction = obj.position - position;
    direction = direction.normalized();

    auto dot = position.dot(obj.position);
    auto lengths = position.length() * obj.position.length();

    auto angle = acos(dot / lengths);

    setRotation(angle, direction);
}
