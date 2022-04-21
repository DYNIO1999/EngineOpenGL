#ifndef DENGINE_SHADER_H
#define DENGINE_SHADER_H
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <string>


namespace  DEngine {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
        std::string TessellationControlShaderSource;
        std::string TessellationEvaluationShaderSource;
        std::string GeometryShaderSource;
        std::string ComputeShaderSource;
    };

    class Shader {
    public:
        Shader(const std::string& _computeShaderPath);
        Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
        Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath, const std::vector<const char*>& _outputNames);
        Shader(const std::string &vertexFilePath,
               const std::string &fragmentFilePath,
               const std::string &tessellationControlFilePath,
               const std::string &tessellationEvaluationFilePath
        );
        Shader(const std::string &vertexFilePath,
               const std::string &geometryFilePath,
               const std::string &fragmentFilePath
        );


        ~Shader();

        void bind() const;

        void unbind() const;


        void setUniform1i(const std::string &name, int value);

        void setUniform1f(const std::string &name, float value);
        void setUniformVec2f(const std::string& _name, glm::vec2 _vector);
        void setUniformVec3f(const std::string& _name, glm::vec3 _vector);
        void setUniformVec4f(const std::string& _name, glm::vec4 _vector);
        void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
        void setUniformMat4f(const std::string &name, glm::mat4 matrix);
        void setUniformMat3f(const std::string &name, glm::mat3 matrix);

    private:
        std::vector<const char*> outputNames;
        bool isTransformFeedbackOn;
        std::string computeShaderFilePath;
        std::string vertexShaderFilePath;
        std::string fragmentShaderFilePath;
        std::string geometryShaderFilePath;
        std::string tessellationControlShaderFilePath;
        std::string tessellationEvaluationShaderFilePath;
        unsigned int shaderID;

        int getUniformLocation(const std::string &name);

        std::unordered_map<std::string, int> UniformLocationCache;

        std::string parseShader(const std::string &filepath, uint _type);

        unsigned int compileShader(unsigned int type, const std::string &source);

        unsigned int createShader(const std::string &_computeShader);
        unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

        unsigned int createShader(const std::string &vertexShader,
                                  const std::string &fragmentShader,
                                  const std::string &tessellationControlShader,
                                  const std::string &tessellationEvaluationShader);


        unsigned int createShader(const std::string &vertexShader,const std::string &geometryShader ,const std::string &fragmentShader);
    };
}
#endif
