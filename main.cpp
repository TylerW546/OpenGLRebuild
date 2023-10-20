// #include <shader.hpp>


#define _USE_MATH_DEFINES
#include <gl.hpp>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cmath>
#include <math.h>

class SimpleSprite : public gl::Sprite {
    float a[2] = {0,0};
    float v[2] = {0,0};
    float aRot = 0;
    float vRot = 0;

    float speed = .05;
    float rotSpeed = .1;

    static constexpr char *spriteFile = "sprites/test_sprite/sprite_square2.jpg";

    public:
    
    SimpleSprite(const gl::GameData &game) {
        moveTo(game.width/2, game.height/2);
    }

    static void initializeTextures(gl::GameData &data) {
        data.resourceManager.loadTexture
                (new gl::Texture(spriteFile, false), "simple_sprite");
    }

    void loadTextures(const gl::GameData &data) override {
        std::cout << "Activating Texture: " << data.resourceManager.texture("simple_sprite") << "\n";
        setActiveTexture(data.resourceManager.texture("simple_sprite"));
    }

    void GameSize_callback(uint16_t width, uint16_t height) override {
        moveTo(width/2, height/2);
    } 

    void update(const gl::GameData &game) override {
        if (game.Keys[GLFW_KEY_LEFT]) {
            a[0] += speed*cos((getRotation()+180)*3.1415926/180);
            a[1] += speed*sin((getRotation()+180)*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_RIGHT]) {
            a[0] += speed*cos((getRotation())*3.1415926/180);
            a[1] += speed*sin((getRotation())*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_UP]) {
            a[0] += speed*cos((getRotation()+270)*3.1415926/180);
            a[1] += speed*sin((getRotation()+270)*3.1415926/180);
        }
        if (game.Keys[GLFW_KEY_DOWN]) {
            a[0] += speed*cos((getRotation()+90)*3.1415926/180);
            a[1] += speed*sin((getRotation()+90)*3.1415926/180);
        }

        if (game.Keys[GLFW_KEY_A]) {
            aRot -= rotSpeed;
        }
        if (game.Keys[GLFW_KEY_D]) {
            aRot += rotSpeed;
        }

        v[0] += a[0];
        v[1] += a[1];
        vRot += aRot;
        a[0] = 0;
        a[1] = 0;
        aRot = 0;

        move(v[0],v[1]);
        rotate(vRot);

        //v[0] *= .92;
        //v[1] *= .92;
        //vRot *= .92;

        if (getPosX() < 0) {
            moveTo(0, getPosY());
            v[0] = 0;
        }
        if (getPosX() > game.width) {
            moveTo(game.width, getPosY());
            v[0] = 0;
        }
        if (getPosY() < 0) {
            moveTo(getPosX(), 0);
            v[1] = 0;
        }
        if (getPosY() > game.height) {
            moveTo(getPosX(), game.height);
            v[1] = 0;
        }


        //rotate(1);
    }

};

int main() {
    gl::Game game(24, 800, 900, "Windows", gl::WindowType::stretch_window);
    
    SimpleSprite::initializeTextures(game.data());
    
    game.loadEntity(new SimpleSprite(game.data()));
    game.execute();

    return 0;
}



// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow *window) {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }



// const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main() {\n"
//         "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\0";


// int main() {

//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     #ifdef __APPLE__
//         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     #endif

//     GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window\n";
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "Failed to initialize GLAD\n";
//         return -1;
//     }

//     glViewport(0, 0, 800, 600);

//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     gl::Shader shader(vertexShaderSource, fragmentShaderSource);

//     // unsigned int vertexShader;
//     // vertexShader = glCreateShader(GL_VERTEX_SHADER);

//     // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     // glCompileShader(vertexShader);

//     // int success;
//     // char infoLog[512];
//     // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     // if (!success) {
//     //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//     //     std::cerr << "ERROR:SHADER:VERTEX: COMPILATION FAILED\n"
//     //             << infoLog << "\n";
//     // }

//     // unsigned int fragmentShader;
//     // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     // glCompileShader(fragmentShader);

//     // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     // if (!success) {
//     //     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//     //     std::cerr << "ERROR:SHADER:FRAGMENT: COMPILATION FAILED\n"
//     //             << infoLog << "\n";
//     // }

//     // unsigned int shaderProgram;
//     // shaderProgram = glCreateProgram();
//     // glAttachShader(shaderProgram, vertexShader);
//     // glAttachShader(shaderProgram, fragmentShader);
//     // glLinkProgram(shaderProgram);

//     // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     // if(!success) {
//     //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//     //     std::cerr << "ERROR:PROGRAM: LINKING FAILED\n"
//     //             << infoLog << "\n";
//     // }

//     // glUseProgram(shaderProgram);

//     // glDeleteShader(vertexShader);
//     // glDeleteShader(fragmentShader);


//     float vertices[] = {
//         0.5f, 0.5f, 0.0f,
//         0.5f, -0.5f, 0.0f,
//         -0.5f, -0.5f, 0.0f,
//         -0.5f,  0.5f, 0.0f
//     };

//     unsigned int indices[] = {
//         0, 1, 3,
//         1, 2, 3
//     };

//     unsigned int VBO, VAO, EBO;

//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);


//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);


//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);


//         // Render to window
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         shader.use();
//         glBindVertexArray(VAO);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//         // glDrawArrays(GL_TRIANGLES, 0, 3);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();

//     return 0;
// }

