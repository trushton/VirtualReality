#ifndef LIGHTS_H
#define LIGHTS_H

//#define GLM_FORCE_RADIANS
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier
#include <Vertex.h>

struct BaseLight
{
    cavr::math::vec3f Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = cavr::math::vec3f(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};

struct DirectionalLight : public BaseLight
{
    cavr::math::vec3f Direction;

    DirectionalLight()
    {
        Direction = cavr::math::vec3f(0.0f, 0.0f, 0.0f);
    }
};

struct PointLight : public BaseLight
{
    cavr::math::vec3f Position;

    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;

    PointLight()
    {
        Position = cavr::math::vec3f(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 0.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};

struct SpotLight : public PointLight
{
    cavr::math::vec3f Direction;
    float Cutoff;

    SpotLight()
    {
        Direction = cavr::math::vec3f(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
};

#define COLOR_WHITE cavr::math::vec3f(1.0f, 1.0f, 1.0f)
#define COLOR_RED cavr::math::vec3f(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN cavr::math::vec3f(0.0f, 1.0f, 0.0f)
#define COLOR_CYAN cavr::math::vec3f(0.0f, 1.0f, 1.0f)
#define COLOR_YELLOW cavr::math::vec3f(1.0f, 1.0f, 0.0f);
#define COLOR_MAGENTA cavr::math::vec3f(1.0f, 0.0f, 1.0f);
#define COLOR_BLUE cavr::math::vec3f(0.0f, 0.0f, 1.0f)

#endif //LIGHTS_H
