#ifndef DENGINE_SHADER_H
#define DENGINE_SHADER_H
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
namespace  DEngine {
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
        std::string TessellationControlShaderSource;
        std::string TessellationEvaluationShaderSource;
    };

    class Shader {
    public:
        Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath);

        Shader(const std::string &vertexFilePath,
               const std::string &fragmentFilePath,
               const std::string &tessellationControlFilePath,
               const std::string &tessellationEvaluationFilePath
        );

        ~Shader();

        void bind() const;

        void unbind() const;


        void setUniform1i(const std::string &name, int value);

        void setUniform1f(const std::string &name, float value);

        void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

        void setUniformMat4f(const std::string &name, glm::mat4 matrix);

    private:
        std::string vertexShaderFilePath;
        std::string fragmentShaderFilePath;
        std::string tessellationControlShaderFilePath;
        std::string tessellationEvaluationShaderFilePath;
        unsigned int shaderID;

        int getUniformLocation(const std::string &name);

        std::unordered_map<std::string, int> UniformLocationCache;

        std::string parseShader(const std::string &filepath);

        unsigned int compileShader(unsigned int type, const std::string &source);

        unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);

        unsigned int createShader(const std::string &vertexShader,
                                  const std::string &fragmentShader,
                                  const std::string &tessellationControlShader,
                                  const std::string &tessellationEvaluationShader);
    };
}
#endif
