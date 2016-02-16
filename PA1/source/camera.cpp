// Reference: http://www.codecolony.de/opengl.htm#Camera2

#include "camera.h"
#include <glm/gtx/rotate_vector.hpp>


Camera::Camera(Engine *eng)
        : engine(eng)
{
    // initialize view
    Position = cavr::math::vec3f(0, 0, 0);
    ViewDir = cavr::math::vec3f(0,0,1);
    RightVector = cavr::math::vec3f(1.0f, 0.0, 0.0f);
    UpVector = cavr::math::vec3f(0.0f, 1.0f, 0.0f);


    RotatedX = RotatedY = RotatedZ = 0.0f;
    movementSpeed = 1.0f;
}

void Camera::Move(cavr::math::vec3f Direction)
{
    Position = (Position + Direction) * movementSpeed;
}

void Camera::RotateX(GLfloat Angle)
{
    RotatedX += Angle;

    // Rotate viewdir around the right vector:
    ViewDir = (ViewDir * cos(Angle * PIdiv180) + UpVector * sin(Angle * PIdiv180)).normalized();

    // now compute the new UpVector (by cross product)
    UpVector = ViewDir.cross(RightVector) * -1.0f;
}

void Camera::RotateY(GLfloat Angle)
{
    RotatedY += Angle;

    ViewDir = (ViewDir * cos(Angle * PIdiv180) - RightVector * sin(Angle * PIdiv180)).normalized();

    RightVector = ViewDir.cross(UpVector);
}

void Camera::RotateZ(GLfloat Angle)
{
    RotatedZ += Angle;

    RightVector = (RightVector * cos(Angle * PIdiv180) + UpVector * sin(Angle * PIdiv180)).normalized();

    //now compute the new UpVector (by cross product)
    UpVector = ViewDir.cross(RightVector) * -1.0f;
}

void Camera::MoveForward(GLfloat Distance)
{
    Position = Position + (ViewDir * -(Distance * movementSpeed));
}

void Camera::StrafeRight(GLfloat Distance)
{
    Position = Position + (RightVector * -(Distance * movementSpeed));
    getView();
}

void Camera::MoveUpward(GLfloat Distance)
{
    Position = Position + (UpVector * (Distance * movementSpeed));
}

void Camera::printOut() {
    cout << Position.x << " | " << Position.y << " | " << Position.z << endl;
    cout << ViewDir.x << " | " << ViewDir.y << " | " << ViewDir.z << endl;
}

cavr::math::mat4f Camera::getView()
{
    update();

    cavr::math::vec3f ViewPoint = Position + ViewDir;
    cavr::math::mat4f view = cavr::math::mat4f::look_at(Position, ViewPoint, UpVector);
    /*cout << Position.x << " | " << Position.y << " | " << Position.z << endl;
    cout << ViewDir.x << " | " << ViewDir.y << " | " << ViewDir.z << endl;
    cout << ViewPoint.x << " | " << ViewPoint.y << " | " << ViewPoint.z << endl;*/


    return view;
}

cavr::math::vec3f Camera::getPos()
{
    return Position;
}


void Camera::rotate(GLfloat x, GLfloat y)
{
    RotatedX -= x * 0.01f;
    RotatedY += y * 0.01f;
    RightVector = ViewDir.cross(UpVector);
}

void Camera::update()
{

    if(RotatedX != 0.0f)
        //ViewDir = glm::rotate(ViewDir, RotatedX, UpVector);

    if(RotatedY != 0.0f)
        //ViewDir = glm::rotate(ViewDir, RotatedY, UpVector.cross(ViewDir));

    RotatedX = RotatedY = 0.0f;
}
