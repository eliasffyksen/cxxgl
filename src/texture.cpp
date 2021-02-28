#include "texture.hpp"

Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
    LOG("Loaded image: " << path << " W:" << width << " H:" << height << " BPP:" << bpp);

    GLCall(glGenTextures(1, &id));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
    unbind();
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &id));
    stbi_image_free(localBuffer);
}

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
