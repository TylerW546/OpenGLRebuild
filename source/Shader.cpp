#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GLFW/glfw.h>

namespace gl {

    Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        std::ifstream vertexFile(vertexPath);
        std::stringstream vertexStream;
        vertexStream << vertexFile.rdbuf();
        std::string vertexSource = vertexStream.str();

        std::ifstream fragmentFile(fragmentPath);
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        std::string fragmentSource = fragmentStream.str();

        loadShader(vertexSource.c_str(), fragmentSource.c_str());
    }



    unsigned int Shader::compileVertexShader(const char* vertexSource) {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        

        int success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "VERTEX SHADER ERROR: COMPILATION FAILED\n"
                    << infoLog << "\n";
            return 0;
        }
        return vertexShader;
    }

    unsigned int Shader::compileFragmentShader(const char* fragmentSource) {
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        int success;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR:SHADER:FRAGMENT: COMPILATION FAILED\n"
                    << infoLog << "\n";
            return 0;
        }
        return fragmentShader;
    }

    bool Shader::loadShader(const char* vertexSource, const char* fragmentSource) {
        unsigned int vertShader = compileVertexShader(vertexSource);
        unsigned int fragShader = compileFragmentShader(fragmentSource);


        id_ = glCreateProgram();
        glAttachShader(id_, vertShader);
        glAttachShader(id_, fragShader);
        glLinkProgram(id_);


        int success;
        glGetProgramiv(id_, GL_LINK_STATUS, &success);
        if(!success) {
            char infoLog[512];
            glGetProgramInfoLog(id_, 512, NULL, infoLog);
            std::cerr << "ERROR:PROGRAM: LINKING FAILED\n"
                    << infoLog << "\n";
        }

        glUseProgram(id_);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        return success;
    }


    // utility uniform functions
    // ------------------------------------------------------------------------
    void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(id_, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]); 
    }
    void Shader::setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(id_, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]); 
    }
    void Shader::setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]); 
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w)  const {
        glUniform4f(glGetUniformLocation(id_, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

}