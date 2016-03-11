#ifndef OBJECT_PAINT_H
#define OBJECT_PAINT_H
#include "Program.h"
#include "lights.h"
#include "Texture.h"
#include <Vertex.h>
#include <iostream>
#include <chrono>


class ObjectPaint : public Program
{
    public:
        cavr::math::mat4f model;
        ObjectPaint();

        void init(std::string texFile);
        void init();


        void enable();

        //void SetPointLight(const PointLight& Lights);
        std::vector<cavr::math::vec3f> positions;
        Texture* tex;
        GLuint object_VB;
        void renderObjects(cavr::math::vec3f cam);

    protected:
        void loadShaders();

        void initShaderProgram();

        void initShaderLocations();


        void bind();
        void unbind();
};


#endif
