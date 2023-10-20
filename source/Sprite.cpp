#include <Sprite.hpp>

#include <glad/glad.h>
#include <GLFW/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

namespace gl {

    SpriteRenderer::SpriteRenderer(Shader shader) :
        shader_(shader)
    {
        std::cout << "starting sp render";
        // configure VAO/VBO
        unsigned int VBO;
        float vertices[] = { 
            // pos      // tex
            -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 
        
            -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 1.0f
        };

        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(VAO_);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);  
        glBindVertexArray(0);
    }

    void SpriteRenderer::setTextureRange
            (float startU, float endU, float startV, float endV) {
        textMap_ = glm::mat4(1.0f);
        textMap_ = glm::translate(textMap_,
                glm::vec3(startU, startV, 0.0f));
        textMap_ = glm::scale(textMap_, 
                glm::vec3((endU-startU), (endV-startV), 1.0f));
        
    }

    void SpriteRenderer::render(glm::vec2 size, glm::vec2 position_,
                glm::vec2 scale, float rotate, const glm::mat4 &projection,
                Texture_base* texture) {
        // prepare transformations
        shader_.use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position_, 0.0f));
        model = glm::rotate(model, glm::radians(rotate),
            glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(size*scale, 1.0f));
        
        
        shader_.setMat4("model", model);
        shader_.setMat4("textureProjection", textMap_);

        shader_.setMat4("projection", projection);
        
        glActiveTexture(GL_TEXTURE0);
        texture->bind();

        glBindVertexArray(this->VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }


    Sprite::Sprite() :
        size_(100,100), position_{0,0}, rotation_(0),
        scale_(1,1), renderer_(nullptr)
    {}

    Sprite::Sprite(Game* game) :
        size_(100,100), position_{0,0}, rotation_(0),
        scale_(1,1), renderer_(game->renderer<SpriteRenderer>())
    {}


    void Sprite::moveTo(float xPos, float yPos) {
        position_[0] = xPos;
        position_[1] = yPos;
    }
    void Sprite::move(float xPos, float yPos) {
        position_[0] += xPos;
        position_[1] += yPos;   
    }

    void Sprite::setRotation(float rotation) {
        rotation_ = rotation;
    }
    void Sprite::rotate(float rotation) {
        rotation_ = fmod(rotation_+rotation, 360);
    }

    void Sprite::setScale(float xScale, float yScale) {
        scale_ = {xScale, yScale};
    }
    void Sprite::scale(float xScale, float yScale) {
        scale_ = {scale_[0]*xScale, scale_[1]*yScale};
    }

    void Sprite::setSize(float xSize, float ySize) {
        size_ = {xSize, ySize};
    }

    void Sprite::render(const glm::mat4& projection) {
        renderer_->render(size_, position_, scale_, rotation_, projection, texture_);
    }  
    // virtual void update()=0;
}