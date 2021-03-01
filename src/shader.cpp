
#include "shader.hpp"

Shader::Shader() {}

Shader::Shader(const std::string& filepath)
{
    load(filepath);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(programId));
}

void Shader::load(const std::string &filename)
{

    std::ifstream stream(filename);

    if (!stream.is_open())
        FATAL_ERR("Unable to open shader file: " << filename);

    LOG("Parsing shader: " << filename);

    ShaderSource::ShaderType currentType = ShaderSource::ShaderType::NONE;

    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                LOG("Reading shader type vertex");
                currentType = ShaderSource::ShaderType::VERTEX;
                continue;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                LOG("Reading shader type fragment");
                currentType = ShaderSource::ShaderType::FRAGMENT;
                continue;
            }
            FATAL_ERR("Unknown shader type in line \"" << line << "\" in shader file: " << filename);
        }
        else if (currentType != ShaderSource::ShaderType::NONE)
        {
            shaderSource.sources[(size_t)currentType] << line << '\n';
        }
    }

    LOG("Done reading shader: " << filename);
}

GLuint Shader::compileShaderType(GLuint type, const std::string &source)
{
    GLCall(GLuint id = glCreateShader(type));
    const char *src = source.c_str();
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
        FATAL_ERR("Exiting");
        return 0;
    }

    return id;
}

void Shader::compile()
{
    if (programId) {
        GLCall(glDeleteProgram(programId));
        locationCache.clear();
    }

    GLCall(programId = glCreateProgram());

    GLuint vs = compileShaderType(GL_VERTEX_SHADER, shaderSource.sources[(size_t)ShaderSource::ShaderType::VERTEX].str());
    GLuint fs = compileShaderType(GL_FRAGMENT_SHADER, shaderSource.sources[(size_t)ShaderSource::ShaderType::FRAGMENT].str());

    GLCall(glAttachShader(programId, vs));
    GLCall(glAttachShader(programId, fs));
    GLCall(glLinkProgram(programId));
    GLCall(glValidateProgram(programId));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

void Shader::bind() const
{
    GLCall(glUseProgram(programId));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int i)
{
    GLCall(glUniform1i(getUniformLocation(name), i));
}

void Shader::setUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}

void Shader::setUniformMatrix4f(const std::string& name, const glm::mat4& u_mat4)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &u_mat4[0][0]));
}

GLint Shader::getUniformLocation(const std::string& name)
{
    auto loc = locationCache.find(name);
    if (locationCache.find(name) != locationCache.end())
        return (*loc).second;

    GLCall(GLint uLoc = glGetUniformLocation(programId, name.c_str()));
    if (uLoc == -1)
        FATAL_ERR("Invalid uniform location");
    locationCache[name] = uLoc;
    return uLoc;
}
