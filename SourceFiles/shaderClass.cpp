#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"


// Default Constructor
Shader::Shader()
    {
        ID = 0;
    }

Shader::Shader(const char* vertexSource, const char* fragmentSource,  const char* geometrySource)
{


    // Create Vertex Shader Object and get its reference
    // OpenGL version of an unsigned integer (positive integers)
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach vertex shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // GPU can't understand source code, so we must compile it now into machine code
    glCompileShader(vertexShader);

    CompileError(vertexShader, "VERTEX");

    // Create fragment shader object and get its reference 
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach fragment shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
     // GPU can't understand source code, so we must compile it now into machine code
    glCompileShader(fragmentShader);

    CompileError(fragmentShader, "FRAGMENT");

    // In order to actually use the shaders, we need to
    // "wrap" them up into a "shader program"
    // Create shader program and get its reference
    ID = glCreateProgram();

    // Attaching the vertex and fragment shaders to the shader program 
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // If we happen to have a geometry shader
    if(geometrySource != nullptr)
    {
        
        GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

        // Attach vertex shader source to the Vertex Shader Object
        glShaderSource(geometryShader, 1, &geometrySource, NULL);
        // GPU can't understand source code, so we must compile it now into machine code
        glCompileShader(geometryShader);

        CompileError(geometryShader, "GEOMETRY");
        glAttachShader(ID, geometryShader);
        // Wrapping the shader program
        glLinkProgram(ID);
        glDeleteShader(geometryShader);
    }
    else
    {
        // Wrapping the shader program
        glLinkProgram(ID);
    }
    // Wrapping the shader program
    

    CompileError(ID, "PROGRAM");
        

    // To keep things tidy, we delete the shaders since they are
    // already in the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}



void Shader::Activate()
{
    glUseProgram(ID);
}

// Setter functions for uniform variables
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set2Float (const std::string &name, float x, float y)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::set2Float (const std::string &name, const glm::vec2 &v2)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), v2.x, v2.y);
}


void Shader::set3Float(const std::string &name, float f1, float f2, float f3) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3);
}

void Shader::set3Float(const std::string &name, const glm::vec3 &v3) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v3.x, v3.y, v3.z);
}

void Shader::set4Float(const std::string &name, float f1, float f2, float f3, float f4) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3, f4);
}

void Shader::set4Float(const std::string &name, const glm::vec4 &v4) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v4.x, v4.y, v4.z, v4.w);
}



void Shader::setMat4(const std::string &name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}




void Shader::Delete()
{
    glDeleteProgram(ID);
}

// Checks for compile errors
void Shader::CompileError(unsigned int shader, std::string type)
{
    GLint  success;
    char infoLog[512];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
          if(!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::SHADER_LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
}
