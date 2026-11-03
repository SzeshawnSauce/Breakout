#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Getting strings from text files and store in variables
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    // Convert and store as character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

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

    // Wrapping the shader program
    glLinkProgram(ID);

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
void Shader::set3Float(const std::string &name, float f1, float f2, float f3) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3);
}

void Shader::set4fv(const std::string &name, glm::mat4 matrix) const
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
