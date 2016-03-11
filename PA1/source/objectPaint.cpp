#include "objectPaint.h"

ObjectPaint::ObjectPaint(){}

void ObjectPaint::init(std::string texFile){
    //load and compile shaders
    loadShaders();

    //link all shaders together
    initShaderProgram();

    //get the variables from the shaders
    initShaderLocations();

    tex = new Texture(texFile, GL_TEXTURE_2D);

    //create the VAO
    glUseProgram(program);
}

void ObjectPaint::enable(){
    glUseProgram(program);
}

void ObjectPaint::loadShaders()
{
    shaders[0] = loadShader("./shaders/grassVS.glsl", GL_VERTEX_SHADER);
    shaders[1] = loadShader("./shaders/grassGS.glsl", GL_GEOMETRY_SHADER);
    shaders[2] = loadShader("./shaders/grassFS.glsl", GL_FRAGMENT_SHADER);
}

void ObjectPaint::initShaderProgram() {
    program = glCreateProgram();
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
    glAttachShader(program, shaders[2]);

    glLinkProgram(program);

    GLint shader_status;
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
    if (!shader_status)
    {
        std::cerr << "Unable to create shadevoid ObjectPaint::initShaderLocations()";

        char buffer[512];
        glGetProgramInfoLog(program, 512, NULL, buffer); // inserts the error into the buffer
        std::cerr << buffer << std::endl;

        exit(1);
    }
}

void ObjectPaint::initShaderLocations()
{
    glUseProgram(program);
    locations["Position"] = glGetAttribLocation(program, "Position");
    locations["model"] = glGetUniformLocation(program, "model");
    locations["gVP"] = glGetUniformLocation(program, "gVP");
    locations["gCameraPos"] = glGetUniformLocation(program, "gCameraPos");
    locations["gColorMap"] = glGetUniformLocation(program, "gColorMap");
}

void ObjectPaint::renderObjects(cavr::math::vec3f cam){

  enable();

  glGenBuffers(1, &object_VB);
  glBindBuffer(GL_ARRAY_BUFFER, object_VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
  model = cavr::math::mat4f::translate(0,0,0) * cavr::math::mat4f::scale(2);
  auto vp = cavr::gfx::getProjection() * cavr::gfx::getView();
  auto camPos = cam;
  this->set("model", model);
  tex->bind(GL_TEXTURE0);
  this->set("gVP", vp);
  this->set("gCameraPos", camPos);
  this->set("gColorMap", 0);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, object_VB);
  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0); //position

  glDrawArrays(GL_POINTS, 0, positions.size());
  glDisableVertexAttribArray(0);

}

void ObjectPaint::bind()
{

}

void ObjectPaint::unbind()
{

}

void ObjectPaint::init()
{

}
