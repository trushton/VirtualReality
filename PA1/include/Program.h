#ifndef PROGRAM_H
#define PROGRAM_H


#include <map>
#include <string>

//#include <glm/glm.hpp>
#include "Vertex.h"
#include <GL/glew.h>
#include <GL/gl.h>

class Program {
    public:

        virtual ~Program() {}

        virtual void init() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        GLint getLocation(const std::string& key);

        void set(const std::string& key, float value);
        void set(const std::string& key, int value);
        void set(const std::string& key, bool value);
        void set(const std::string& key, const cavr::math::vec2f& value);
        void set(const std::string& key, const cavr::math::vec3f& value);
        void set(const std::string& key, const cavr::math::vec4f& value);
        void set(const std::string& key, const cavr::math::mat3f& value);
        void set(const std::string& key, const cavr::math::mat4f& value);

    protected:
        static GLuint loadShader(const char* fileName, GLenum shaderType);
        virtual void loadShaders() = 0;
        virtual void initShaderProgram() = 0;
        virtual void initShaderLocations() = 0;

        GLuint program;
        GLuint shaders[3];
        std::map<std::string, GLint> locations;
    };


#endif
