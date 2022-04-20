#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>
#include "Renderer.h"

namespace DEngine{
    Shader::Shader(const std::string &_computeShaderPath):
            computeShaderFilePath(_computeShaderPath),
            isTransformFeedbackOn(false),
            shaderID(0)
    {
        ShaderProgramSource source{};
        source.ComputeShaderSource= parseShader(computeShaderFilePath, GL_COMPUTE_SHADER);
        shaderID = createShader(source.ComputeShaderSource);
    }
    Shader::Shader(const std::string &vertexFilePath,
                   const std::string &fragmentFilePath,
                   const std::vector<const char*>& _outputNames):
            vertexShaderFilePath(vertexFilePath),
            fragmentShaderFilePath(fragmentFilePath),
            outputNames(_outputNames),
            isTransformFeedbackOn(true),
            shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource= parseShader(vertexShaderFilePath, GL_VERTEX_SHADER);
        source.FragmentSource= parseShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
        shaderID = createShader(source.VertexSource, source.FragmentSource);
    }
    Shader::Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath):
            vertexShaderFilePath(vertexFilePath),
            fragmentShaderFilePath(fragmentFilePath),
            isTransformFeedbackOn(false)
            ,shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource= parseShader(vertexShaderFilePath, GL_VERTEX_SHADER);
        source.FragmentSource= parseShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
        shaderID = createShader(source.VertexSource, source.FragmentSource);
    }

    Shader::Shader(const std::string &vertexFilePath,
           const std::string &geometryFilePath,
           const std::string &fragmentFilePath
    ):
    vertexShaderFilePath(vertexFilePath),
    geometryShaderFilePath(geometryFilePath),
    fragmentShaderFilePath(fragmentFilePath),
    isTransformFeedbackOn(false),
    shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource = parseShader(vertexShaderFilePath, GL_VERTEX_SHADER);
        source.GeometryShaderSource = parseShader(geometryShaderFilePath, GL_GEOMETRY_SHADER);
        source.FragmentSource = parseShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
        shaderID = createShader(source.VertexSource, source.GeometryShaderSource, source.FragmentSource);
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
            isTransformFeedbackOn(false),
            shaderID(0)
    {
        ShaderProgramSource source{};
        source.VertexSource= parseShader(vertexShaderFilePath, GL_VERTEX_SHADER);
        source.FragmentSource= parseShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
        source.TessellationControlShaderSource = parseShader(tessellationControlShaderFilePath, GL_TESS_CONTROL_SHADER);
        source.TessellationEvaluationShaderSource = parseShader(tessellationEvaluationShaderFilePath, GL_TESS_EVALUATION_SHADER);
        shaderID = createShader(source.VertexSource,
                                source.FragmentSource,
                                source.TessellationControlShaderSource,
                                source.TessellationEvaluationShaderSource);
    }
    Shader::~Shader()
    {
        glDeleteProgram(shaderID);
    }

    std::string Shader::parseShader(const std::string &filepath, uint _type)
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

            std::string shaderType;
            switch (_type) {
                case GL_VERTEX_SHADER:
                    shaderType = "VERTEX";
                    break;
                case GL_FRAGMENT_SHADER:
                    shaderType = "FRAGMENT";
                    break;
                case GL_TESS_CONTROL_SHADER:
                    shaderType = "TESS_CONTROL";
                    break;
                case GL_TESS_EVALUATION_SHADER:
                    shaderType = "TESS_EVALUATION";
                    break;
                case GL_GEOMETRY_SHADER:
                    shaderType = "GEOMETRY";
                    break;
                case GL_COMPUTE_SHADER:
                    shaderType = "COMPUTE";
                    break;
            }
            DENGINE_ERROR("Cant read file {} SHADER \tfilepath {}", shaderType, filepath);
            DENGINE_ERROR(e.what());
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
            std::string shaderType;
            switch (type) {
                case GL_VERTEX_SHADER:
                    shaderType = "VERTEX";
                    break;
                case GL_FRAGMENT_SHADER:
                    shaderType = "FRAGMENT";
                    break;
                case GL_TESS_CONTROL_SHADER:
                    shaderType = "TESS_CONTROL";
                    break;
                case GL_TESS_EVALUATION_SHADER:
                    shaderType = "TESS_EVALUATION";
                    break;
                case GL_GEOMETRY_SHADER:
                    shaderType = "GEOMETRY";
                    break;
                case GL_COMPUTE_SHADER:
                    shaderType = "COMPUTE";
                    break;
            }
            DENGINE_ERROR("Failed to compile {} SHADER!",shaderType);
            DENGINE_ERROR(message);
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
        if(isTransformFeedbackOn) {
            DENGINE_ERROR("TRANSFORM FEEDBACK IS ON!");

            glTransformFeedbackVaryings(program, static_cast<int>(outputNames.size()), outputNames.data(),
                                        GL_SEPARATE_ATTRIBS);
        }
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }


    unsigned int Shader::createShader(const std::string &vertexShader,const std::string &geometryShader ,const std::string &fragmentShader){

        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int gs =  compileShader(GL_GEOMETRY_SHADER, geometryShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


        glAttachShader(program, vs);
        glAttachShader(program, gs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(gs);
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
    unsigned int Shader::createShader(const std::string &_computeShader){
        unsigned int program = glCreateProgram();
        unsigned int cs = compileShader(GL_COMPUTE_SHADER, _computeShader);
        glAttachShader(program, cs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(cs);
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

    void Shader::setUniformMat3f(const std::string &name, glm::mat3 matrix){
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void Shader::setUniformVec3f(const std::string &_name, glm::vec3 _vector) {
        glUniform3f(getUniformLocation(_name), _vector.x, _vector.y, _vector.z);
    }
    void Shader::setUniformVec4f(const std::string& _name, glm::vec4 _vector){
        glUniform4f(getUniformLocation(_name), _vector.x, _vector.y, _vector.z, _vector.w);
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