
#include "Program.h"

#define GLM_FORCE_RADIANS

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

GLint Program::getLocation(const std::string &key)
{
    return locations.at(key);
}

void Program::set(const std::string &key, float value)
{
    glUniform1f(locations.at(key), value);
}

void Program::set(const std::string &key, int value)
{
    glUniform1i(locations.at(key), value);
}

void Program::set(const std::string &key, bool value)
{
    glUniform1i(locations.at(key), value);
}

void Program::set(const std::string &key, const cavr::math::vec2f &value)
{
    glUniform2fv(locations.at(key), 1, (&value[0]));
}

void Program::set(const std::string &key, const cavr::math::vec3f &value)
{
    glUniform3fv(locations.at(key), 1, (&value[0]));
}

void Program::set(const std::string &key, const cavr::math::vec4f &value)
{
    glUniform4fv(locations.at(key), 1, (&value[0]));
}

void Program::set(const std::string &key, const cavr::math::mat3f &value)
{
    glUniformMatrix3fv(locations.at(key), 1, GL_FALSE, (value).v);
}

void Program::set(const std::string &key, const cavr::math::mat4f &value)
{
    glUniformMatrix4fv(locations.at(key), 1, GL_FALSE, (value).v);
}

GLuint Program::loadShader(const char *fileName, GLenum shaderType)
{
    std::ifstream fstream;
    std::string line;
    std::string shaderStr = "";

    // read in Shader data from a file
    fstream.open(fileName);
    if (!fstream.is_open())
    {
        std::cout << "Could not open Shader file: " << fileName << std::endl;
        exit(1);
    }

    getline(fstream, line);
    shaderStr += line;
    shaderStr += '\n';
    while (getline(fstream, line))
    {
        shaderStr += line;
    }
    fstream.close();

    const char *shaderData = shaderStr.c_str();

    //compile the Shader
    GLuint shader = glCreateShader(shaderType);
    char buffer[512];
    GLint shader_status;
    glShaderSource(shader, 1, &shaderData, NULL);
    glCompileShader(shader);
    glGetShaderInfoLog(shader, 512, NULL, buffer);

    //check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);

    if (!shader_status)
    {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);

        std::string shaderTypeStr = "shader";
        std::cerr << "Failed to compile " << shaderTypeStr << " loaded from " << fileName << std::endl;
        std::cerr << "Compile Error: " << buffer << std::endl;
        //engine->stop();
        exit(1);
    }

    return shader;
}

void Program::bind(){

}

void Program::unbind(){

}
