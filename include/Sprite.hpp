#pragma once

namespace gl{
class SpriteRender;
class Sprite;
}

#include "Entity.hpp"
#include "Shader.hpp"

#include <iostream>

#include "deps.h"

namespace gl {
    class SpriteRenderer {
        Shader shader_;
        unsigned int VAO_;
        glm::mat4 textMap_; 

        public:

        static constexpr char* VERTEX_PATH = "shaders\\sprite\\sprite.vs";
        static constexpr char* FRAGMENT_PATH = "shaders\\sprite\\sprite.frag";

        SpriteRenderer(Shader shader);
        ~SpriteRenderer();

        void setTextureRange(float startU, float endU, float startV, float endV);

        void render(glm::vec2 size, glm::vec2 position, glm::vec2 scale,
                float rotate, const glm::mat4 &windowModel, Texture_base* texture);
        
    };


    class Sprite : public Entity {

        SpriteRenderer* renderer_; 
        Texture_base* texture_;

        glm::vec2 position_, scale_, size_;
        float rotation_;

        public:

        Sprite();
        Sprite(Game* game);
        ~Sprite() {}

        virtual void loadRenderer(Game* game) override {
            renderer_ = game->renderer<SpriteRenderer>();
        }
        virtual SpriteRenderer* getRenderer() {return renderer_;}

        virtual void loadTextures(const GameData &data) override {}
        void setActiveTexture(Texture_base* texture) {
            size_ = {texture->getWidth(), texture->getHeight()};
            texture_ = texture;
        }
        Texture_base* getTexture() {return texture_;}

        float getPosX() {return position_[0];}
        float getPosY() {return position_[1];}
        float getRotation() {return rotation_;}
        float getScaleX() {return scale_[0];}
        float getScaleY() {return scale_[1];}

        void moveTo(float xPos, float yPos);
        void move(float xPos, float yPos);
        void setX(float xPos) {position_[0] = xPos;}
        void setY(float yPos) {position_[1] = yPos;}
        void moveX(float xPos) {position_[0] += xPos;}
        void moveY(float yPos) {position_[1] += yPos;}
        
        void setRotation(float rotation);
        void rotate(float rotation);
        float rotation() {return rotation_;}

        void setScale(float xScale, float yScale);
        void scale(float xScale, float yScale);

        void setSize(float xSize, float ySize);

        virtual void render(const glm::mat4& windowModel) override;
        virtual void update(const gl::GameData& gameData) override {};

    };

}