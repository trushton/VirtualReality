// Reference: http://www.codecolony.de/opengl.htm#Camera2
#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.1415926f
#define PIdiv180 (PI/180.0f)

#include <GL/glew.h>
#include <GL/gl.h>
#include "math.h"
#include <iostream>
#include <Vertex.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine.h"

using namespace std;

class Camera
{
public:

    Camera(Engine *eng);

    void Move(cavr::math::vec3f Direction);

    void RotateX(GLfloat Angle);
    void RotateY(GLfloat Angle);
    void RotateZ(GLfloat Angle);

    void MoveForward(GLfloat Distance);
    void MoveUpward(GLfloat Distance);
    void StrafeRight(GLfloat Distance);

    void rotate(GLfloat, GLfloat);
    void update();
    void printOut();

    cavr::math::mat4f getView();
    cavr::math::vec3f getPos();
    cavr::math::mat4f Rogerify(glm::mat4 src);
    glm::vec3 RogerToGLMVec3(cavr::math::vec3f src);
    cavr::math::vec3f glmToCavrVec3(glm::vec3 src);

//        cavr::math::vec3 getPos() const { return pos; }
    //cavr::math::vec3 getOrientation() const { return orientation; }
    GLfloat totalX;
    GLfloat totalY;
    GLfloat movementSpeed;
    cavr::math::vec3f ViewDir;


private:
    cavr::math::vec3f RightVector;
    cavr::math::vec3f UpVector;
    cavr::math::vec3f Position;

    //glm::vec3 pos, orientation ,up;
    //GLfloat rotateX, rotateY, speed, sensitivity, boost;

    GLfloat RotatedX, RotatedY, RotatedZ;


    Engine *engine;
};


#endif
