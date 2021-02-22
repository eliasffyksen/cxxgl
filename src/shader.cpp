
#include "shader.hpp"

void readShader(const std::string& filename, ShaderSource &shaderSource) {

    std::ifstream stream(filename);

    if (!stream.is_open())
        FATAL_ERR("Unable to open shader file: " << filename);

    LOG("Parsing shader: " << filename);

    ShaderSource::ShaderType currentType = ShaderSource::ShaderType::NONE;

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                LOG("Reading shader type vertex");
                currentType = ShaderSource::ShaderType::VERTEX;
                continue;
            } else if (line.find("fragment") != std::string::npos) {
                LOG("Reading shader type fragment");
                currentType = ShaderSource::ShaderType::FRAGMENT;
                continue;
            }
            FATAL_ERR("Unknown shader type in line \"" << line << "\" in shader file: " << filename);
        } else if (currentType != ShaderSource::ShaderType::NONE) {
            shaderSource.sources[(size_t) currentType] << line << '\n';
        }
    }

    LOG("Done reading shader: " << filename);
}

ShaderSource::ShaderSource(const std::string& filename) {
    readShader(filename, *this);
}

GLuint compileShader(GLuint type, const std::string& source)
{
    GLClearError();
    GLuint id = glCreateShader(type);
    GLPrintError();
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        ERR("Failed top compile shader");
        ERR("GL ERR: " << message);
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

GLuint createShader(const ShaderSource& source)
{
    GLClearError();
    GLuint program = glCreateProgram();
    GLPrintError();
    GLuint vs = compileShader(GL_VERTEX_SHADER, source.sources[(size_t) ShaderSource::ShaderType::VERTEX].str());
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, source.sources[(size_t) ShaderSource::ShaderType::FRAGMENT].str());

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

