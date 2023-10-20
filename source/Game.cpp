#include <Game.hpp>
#include <Sprite.hpp>
#include <iostream>

namespace gl {
    Game::Game(uint32_t tps, uint16_t gameWidth, uint16_t gameHeight,
            const char* windowTitle, WindowType windowType) :
        gameData_{.width = gameWidth, .height = gameHeight, .tps = tps},
        window_(nullptr),
        entities_(new EntityList())
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        window_ = new Window(this, windowType, gameWidth, gameHeight, windowTitle);
        std::cout << "0";
        SpriteRenderer *spriteRenderer = new SpriteRenderer
            (Shader(SpriteRenderer::VERTEX_PATH, SpriteRenderer::FRAGMENT_PATH));
        std::cout << "1";
        loadRenderer<SpriteRenderer>(spriteRenderer);
        std::cout << "2";

    }

    Game::~Game() {
        glfwTerminate();
        if (window_)
            delete window_;
    }


    bool Game::setGameSize(uint16_t width, uint16_t height) {
        gameData_.width = width;
        gameData_.height = height;
        entities_->call(&Entity::GameSize_callback, width, height);
    }

    void Game::pressKey(int key) {
        gameData_.Keys[key] = true;
    }

    void Game::releaseKey(int key) {
        gameData_.Keys[key] = false;
    }


    void Game::loadEntity(Entity* entity) {
        entities_->appendFront(entity);
        entity->loadRenderer(this);
        entity->loadTextures(gameData_);
    }

    void Game::execute() {
        // std::cout << "Starting execution\n";
        while (!window_->shouldClose()) {
            // std::cout << "setting back drop\n";
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            // std::cout << "rendering entities\n";
            entities_->render(window_->projection());
            // std::cout << "updating entities\n";
            entities_->update(gameData_);
        
            // std::cout << "swapping buffer then polling events\n";
            window_->swapBuffers();
            glfwPollEvents();
            // std::cout << "End of execution phase\n\n";
        }
    }
}