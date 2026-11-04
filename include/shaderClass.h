#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
    public:
    // Reference to object
    GLuint ID;

    // Default Constructor
    Shader();
    // Constructor that takes in the vertex and fragment source code
    Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

    
    void Activate();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void set2Float (const std::string &name, float x, float y);
    void set2Float (const std::string &name, const glm::vec2 &v2);
    void set3Float(const std::string &name, float f1, float f2, float f3) const;
    void set3Float(const std::string &name, const glm::vec3 &v3) const;
    void set4Float(const std::string &name,float f1, float f2, float f3, float f4) const;
    void set4Float(const std::string &name, const glm::vec4 &v4) const;
    void setMat4(const std::string &name, glm::mat4 matrix) const;
    void Delete();
    void CompileError(unsigned int shader, std::string type);

};




#endif
