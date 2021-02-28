#pragma once

#include <GL/glew.h>
#include <stb/stb_image.h>
#include <string>

#include "error.hpp"

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() { return width; }
    inline int getHeight() { return height; }

private:
    GLuint id;
    unsigned char* localBuffer = nullptr;
    int width, height, bpp;
};

