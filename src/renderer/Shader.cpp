#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>
#include "Renderer.h"

namespace DEngine{
    Shader::Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath):
            vertexShaderFilePath(vertexFilePath),
            fragmentShaderFilePath(fragmentFilePath)
            ,shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource= parseShader(vertexShaderFilePath);
        source.FragmentSource= parseShader(fragmentShaderFilePath);
        shaderID = createShader(source.VertexSource, source.FragmentSource);
    }
    Shader::Shader(const std::string &vertexFilePath,
           const std::string &fragmentFilePath,
           const std::string &tessellationControlFilePath,
           const std::string &tessellationEvaluationFilePath
    ):
            vertexShaderFilePath(vertexFilePath),
            fragmentShaderFilePath(fragmentFilePath),
            tessellationControlShaderFilePath(tessellationControlFilePath),
            tessellationEvaluationShaderFilePath(tessellationEvaluationFilePath),
            shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource= parseShader(vertexShaderFilePath);
        source.FragmentSource= parseShader(fragmentShaderFilePath);
        source.TessellationControlShaderSource = parseShader(tessellationControlShaderFilePath);
        source.TessellationEvaluationShaderSource = parseShader(tessellationEvaluationShaderFilePath);
        shaderID = createShader(source.VertexSource,
                                source.FragmentSource,
                                source.TessellationControlShaderSource,
                                source.TessellationEvaluationShaderSource);
    }
    Shader::~Shader()
    {
        glDeleteProgram(shaderID);
    }

    std::string Shader::parseShader(const std::string &filepath)
    {
        std::string sourceCode;
        std::ifstream sourceCodeFile;
        sourceCodeFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            sourceCodeFile.open(filepath);
            std::stringstream shaderStream;
            shaderStream <<sourceCodeFile.rdbuf();
            sourceCodeFile.close();
            sourceCode = shaderStream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << '\n';
        }
        return sourceCode;
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string &source)
    {
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::string shaderType = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
            std::cout << "Failed to compile " << shaderType << "shader" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
    {

        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
    unsigned int Shader::createShader(const std::string &vertexShader,
                                      const std::string &fragmentShader,
                                      const std::string &tessellationControlShader,
                                      const std::string &tessellationEvaluationShader)
    {

        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int tcs = compileShader(GL_TESS_CONTROL_SHADER, tessellationControlShader);
        unsigned int tes =  compileShader(GL_TESS_EVALUATION_SHADER, tessellationEvaluationShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, tcs);
        glAttachShader(program, tes);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(tcs);
        glDeleteShader(tes);
        glDeleteShader(fs);

        return program;
    }

    void Shader::bind() const
    {
        glUseProgram(shaderID);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::setUniform1i(const std::string &name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setUniform1f(const std::string &name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::setUniformMat4f(const std::string &name, glm::mat4 matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    int Shader::getUniformLocation(const std::string &name)
    {
        if (UniformLocationCache.find(name) != UniformLocationCache.end())
        {
            return UniformLocationCache[name];
        }

        int location = glGetUniformLocation(shaderID, name.c_str());
        if (location == -1)
        {

            std::cout << "Warning: uniform " << name << "doesn't exist" << std::endl;
        }
        UniformLocationCache[name] = location;
        return location;
    }

}