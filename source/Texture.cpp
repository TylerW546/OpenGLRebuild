#include <deps.h>

#include <Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

namespace gl {

    Texture::Texture()
        : width(0), height(0), internal_Format(GL_RGB), image_Format(GL_RGB),
        wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR),
        filter_Max(GL_LINEAR)
    {
        glGenTextures(1, &this->ID);
    }

    Texture::Texture(const char* file, bool alpha)
        : width(0), height(0), internal_Format(GL_RGB), image_Format(GL_RGB),
        wrap_S(GL_REPEAT), wrap_T(GL_REPEAT), filter_Min(GL_LINEAR),
        filter_Max(GL_LINEAR)
    {
        glGenTextures(1, &this->ID);
        generate(file, alpha);
    }

    Texture::~Texture() {
        if (this->ID)
            glDeleteTextures(1, &this->ID);
    }

    void Texture::generate(const char* file, bool alpha)
    {
        int width, height, nrChannels;
        unsigned char* data;

        if (alpha) {
            internal_Format = GL_RGBA;
            image_Format = GL_RGBA;
        }
        

        data = stbi_load(file, &width, &height, &nrChannels, 0);
        if (!data) std::cerr << "ERRROR OPENING TEXTURE: " << file << "\n";

        this->width = width;
        this->height = height;

        // create Texture
        this->bind();
        glTexImage2D(GL_TEXTURE_2D, 0, this->internal_Format, this->width, this->height, 0, this->image_Format, GL_UNSIGNED_BYTE, data);
        // set Texture wrap and filter modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);
        
        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }

}