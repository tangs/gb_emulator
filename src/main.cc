#include <print>
#include <iostream>

//#include "ncurses.h"

#include <chrono>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cartridge.h"
#include "graphic.h"
#include "shader.h"

int refresh(const char* licName, const char* title, Graphic* graphic) {
    constexpr auto PIXEL_SCALE_X = 1;
    constexpr auto PIXEL_SCALE_Y = 4;
    constexpr auto W = Define::SCREEN_WIDTH / PIXEL_SCALE_X;
    constexpr auto H = Define::SCREEN_HEIGHT / PIXEL_SCALE_Y;

//    clear();
//    mvaddstr(0, 0, licName);
//    mvaddstr(1, 0, title);

    constexpr auto OFF_ROW = 2;

//    for (int i = 0; i <= W + 1; ++i) {
//        mvaddch(OFF_ROW, i, '-');
//        mvaddch(OFF_ROW + H + 1, i, '-');
//    }
//
//    for (int i = OFF_ROW + 1; i <= H + OFF_ROW; ++i) {
//        mvaddch(i, 0, '|');
//        mvaddch(i, W + 1, '|');
//    }

//    for (int i = 0; i < H; ++i) {
//        for (int j = 0; j < W; ++j) {
//            auto pixel = graphic->pixels[i * PIXEL_SCALE_X][j * PIXEL_SCALE_Y];
//            if (pixel != 0) {
//                auto r = i + OFF_ROW + 1;
//                auto c = j + 1;
//                mvaddch(r, c, '*');
//            }
//        }
//    }
//
//    move(LINES - 1, 0);
//    refresh();
    return 0;
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

constexpr auto vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

out vec4 vertexColor; // 为片段着色器指定一个颜色输出

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);
    vertexColor = vec4(aColor, 1.0);
}
)";

constexpr auto fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）

void main()
{
    FragColor = vertexColor;
}
)";

int main() {
//    u8 buf[1024 * 1024];
//    auto file = fopen("/Users/tangs/Documents/console_game_boy_emulator/rooms/Tetris (Japan) (En).gb", "rb");
//    auto len = fread(buf, sizeof buf[0], sizeof buf, file);
//    fclose(file);
//
//    auto* cartridge = (CartridgeHeader*)(buf + 0x100);
//    auto licName = get_cartridge_lic_code_name(cartridge->lic_code);
//
//    Graphic graphic;
//
//    constexpr auto w = 6;
//    constexpr auto h = 8;
//
//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < w; j++) {
//            int idx = i * w + j;
//            auto pixel = cartridge->logo[idx];
//            for (int k = 0; k < 4; ++k) {
//                graphic.pixels[i][j * 4 + k] = pixel & (1 << k);
//            }
//        }
//    }
//
//    // 进行刷新，使内容显示到屏幕上
////    initscr();
////    cbreak();
////    noecho();
////
////    mvaddstr(0, 0, "+++++++++++++++++++++++++");
////    mvaddstr(LINES - 1, 0, "-------------------------");
////    mvaddstr(1, 0, "**********");
////    mvaddstr(2, 0, "** ** * **");
////    move(3, 0);
////    refresh();
//
//    double delayTime = 1.0 / 60;
//    for (int i = 0; i < 10000; ++i) {
//        usleep((unsigned int)(delayTime * 1000 * 1000));
//
//        refresh(licName, cartridge->title, &graphic);
////        auto str = std::to_string(i);
////
////        clear();
////        mvaddstr(0, 0, "+++++++++++++++++++++++++");
////        mvaddstr(LINES - 1, 0, "-------------------------");
////        mvaddstr(1, 0, str.c_str());
////        mvaddstr(2, 0, str.c_str());
////        move(3, 0);
////        refresh();
//    }

//    usleep(100 * 1000 * 1000);
//    endwin();

    constexpr auto SCREEN_SCALE = 1;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    auto window = glfwCreateWindow(
            Define::SCREEN_WIDTH * SCREEN_SCALE,
            Define::SCREEN_HEIGHT * SCREEN_SCALE,
            "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

//    glViewport(0, 0, Define::SCREEN_WIDTH * SCREEN_SCALE, Define::SCREEN_HEIGHT * SCREEN_SCALE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, sizeof infoLog, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, sizeof infoLog, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FLAG::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof infoLog, nullptr, infoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);

    auto deltaTime = std::chrono::milliseconds(1000 / 60);
    auto r = 0.01f;

    constexpr auto pixelsLen = Define::SCREEN_WIDTH * Define::SCREEN_HEIGHT * SCREEN_SCALE;
    float vertices[pixelsLen * 6];

    {
        int idx = 0;
        for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
                float percentX = (float) j / Define::SCREEN_WIDTH;
                float percentY = (float) i / Define::SCREEN_HEIGHT;
                float x = percentX * 2.0f - 1.0f;
                float y = percentY * 2.0f - 1.0f;

                // position(x, y, z)
                vertices[idx++] = x;
                vertices[idx++] = y;
                vertices[idx++] = 0.0f;

                // color(r, g, b)
//                vertices[idx++] = 0;
//                vertices[idx++] = percentY;
//                vertices[idx++] = 0.0f;
                vertices[idx++] = 1.0f;
                vertices[idx++] = 0.0f;
                vertices[idx++] = 0.0f;
            }
        }
    }

//    float vertices[] = {
//            0.5f, 0.5f, 0.0f,   // 右上角
//            0.5f, -0.5f, 0.0f,  // 右下角
//            -0.5f, -0.5f, 0.0f, // 左下角
//            -0.5f, 0.5f, 0.0f   // 左上角
//    };
//    unsigned int indices[] = {
//            // 注意索引从0开始!
//            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
//            // 这样可以由下标代表顶点组合成矩形
//
//            0, 1, 3, // 第一个三角形
//            1, 2, 3  // 第二个三角形
//    };

    unsigned int VBO;
    unsigned int VAO;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    auto start = std::chrono::high_resolution_clock::now();
    auto updated = false;

    while (!glfwWindowShouldClose(window)) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (!updated && duration.count() > 1) {
            updated = true;
            std::cout << "update colors." << std::endl;
            int idx = 0;
            for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
                for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
                    idx += 3;

                    // color(r, g, b)
                    vertices[idx++] = 1.0f;
                    vertices[idx++] = 1.0f;
                    vertices[idx++] = 0.0f;
                }
            }

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            if (ptr) {
                // 更新数据
                memcpy(ptr, vertices, sizeof(vertices));
                // 取消映射
                glUnmapBuffer(GL_ARRAY_BUFFER);
            }
        }

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_POINTS, 0, pixelsLen);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
//        std::this_thread::sleep_for(deltaTime);
        r += 0.001f;
    }

    glfwTerminate();
    return 0;
}
