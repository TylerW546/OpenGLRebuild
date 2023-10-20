#pragma once


namespace gl {

    class Texture_base {
        public:
        virtual ~Texture_base() {}
        virtual void bind() const=0;
        virtual unsigned int getWidth()=0;
        virtual unsigned int getHeight()=0;

        // Map width and height to range 0-1
        virtual float mapWidth(unsigned width)=0;
        virtual float mapHeight(unsigned height)=0; 
        
    };

    class Texture : public Texture_base
    {
        public:

        // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        unsigned int ID;

        // texture image dimensions
        unsigned int width, height; // width and height of loaded image in pixels

        // texture Format
        unsigned int internal_Format; // format of texture object
        unsigned int image_Format; // format of loaded image

        // texture configuration
        unsigned int wrap_S; // wrapping mode on S axis
        unsigned int wrap_T; // wrapping mode on T axis
        unsigned int filter_Min; // filtering mode if texture pixels < screen pixels
        unsigned int filter_Max; // filtering mode if texture pixels > screen pixels

        Texture();
        Texture(const char* file, bool alpha);
        virtual ~Texture();

        // generates texture from image data
        void generate(const char* file, bool alpha);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void bind() const override;

        // Getters for  width and height
        unsigned int getWidth() override {return width;}
        unsigned int getHeight() override {return height;}

        // Map width and height to range 0-1
        float mapWidth(unsigned width) override {return this->width / width;}
        float mapHeight(unsigned height) override {return this->height / height;}
    };

}