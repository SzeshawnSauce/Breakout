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
    // Constructor that takes in the vertex and fragment source code
    Shader(const char* vertexFile, const char* fragmentFile);

    
    void Activate();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void set3Float(const std::string &name, float f1, float f2, float f3) const;
    void set4fv(const std::string &name, glm::mat4 matrix) const;
    void Delete();
    void CompileError(unsigned int shader, std::string type);

};




#endif
