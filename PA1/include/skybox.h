#ifndef Skybox_H
#define Skybox_H

#include "Shader.h"
//#include "model.h"
#include "Program.h"
#include <vector>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include <Vertex.h>

#define INDEX_BUFFER 0
#define POS_VB 1


class Skybox : public Program  {

public:

    Skybox();

    virtual void init();
    virtual void bind();
    virtual void unbind();


    void tick(float dt);
    void render(cavr::math::vec3f pos);

private:
    void loadShaders();
    void initShaderProgram();
    void initShaderLocations();


    // The GLSL program handle
    GLuint m_VAO;


    // transform matrices
    cavr::math::vec3f position;
    cavr::math::mat4f view;
    cavr::math::mat4f projection;

    string m_fileNames[6];
    GLuint skyboxTexture;

};


#endif //Skybox_H
