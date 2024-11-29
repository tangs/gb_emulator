#include <print>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cartridge.h"
#include "graphic.h"
#include "shader.h"
#include "screen.h"

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

u8 calcCheckSum(const u8* rom_data) {
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; ++address) {
        checksum = checksum - rom_data[address] - 1;
    }
    return checksum;
}

void printRomInfo(const u8* buf) {
    auto cartridge = (CartridgeHeader*)(buf + 0x100);
    auto licName = cartridge->get_cartridge_lic_code_name();
    std::cout << "title: " << cartridge->title << std::endl;
    std::cout << "version: " << (uint32_t)cartridge->version << std::endl;
    std::cout << "lic name: " << licName << std::endl;
    std::cout << "cartridge type: " << (int)cartridge->cartridge_type << std::endl;
    std::cout << "rom size: " << 32 * (1 << cartridge->rom_size) << "KB" << std::endl;
    std::cout << "ram size: " << (int)cartridge->ram_size << std::endl;
    auto checkSum = calcCheckSum(buf);
    std::cout << "check sum: " << (int)cartridge->checksum << ", "
        << (int)checkSum << ", " << (cartridge->checksum == checkSum) << std::endl;
}

int main() {
    u8 buf[1024 * 1024];
    auto file = fopen("/Users/tangs/Documents/console_game_boy_emulator/rooms/Tetris (Japan) (En).gb", "rb");
    auto _len = fread(buf, sizeof buf[0], sizeof buf, file);
    fclose(file);

    auto* cartridge = (CartridgeHeader*)(buf + 0x100);
    printRomInfo(buf);

//    Graphic graphic;
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

    auto deltaTime = std::chrono::milliseconds(1000 / 60);

    Screen screen;
    screen.Clear(Color(0xff, 0, 0));
    constexpr auto pixelsLen = Screen::VERTICES_LEN / Screen::COUNT_PER_GROUP;


    constexpr auto w = 4;
    constexpr auto h = 12;

//    int offX = 50;
//    int offY = 60;

    std::array<std::array<bool, Define::SCREEN_WIDTH>, Define::SCREEN_HEIGHT> dp = {};

    screen.Clear({0, 0, 0});
//            screen.SetPixel(40, 40, 1.0f, 1.0f, 1.0f);
    auto bits = cartridge->get_logo_bitmap();
    auto offX = (Define::SCREEN_WIDTH - 48) / 2;
    auto offY = (Define::SCREEN_HEIGHT - 8) / 2;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 48; ++j) {
            if (!bits[i][j]) continue;
            int x = j + offX;
            int y = (7 - i) + offY;
            dp[y][x] = true;
            screen.SetPixel({x, y}, {0xff, 0xff, 0x0});
        }
    }

    unsigned int VBO;
    unsigned int VAO;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen.vertices_), screen.vertices_, GL_DYNAMIC_DRAW);

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

    auto shader = Shader("res/vShader.vs", "res/fShader.fs");

    while (!glfwWindowShouldClose(window)) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        auto count = duration.count();
        auto val = (u8)((std::sin((float)count / 1000.f) + 1.0f) / 2.0f * 255);
        auto col = Color{val, 0, 0};
        for (int i = 0; i < Define::SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < Define::SCREEN_WIDTH; ++j) {
                if (dp[i][j]) continue;
                screen.SetPixel({j, i}, col);
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        auto ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if (ptr) {
            // 更新数据
            memcpy(ptr, screen.vertices_, sizeof(screen.vertices_));
            // 取消映射
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

//        if (!updated && duration.count() > 1) {
//            updated = true;
//            std::cout << "update colors." << std::endl;
////            screen.Clear(1.0f, 0.0f, 0.0f);
////            screen.SetPixel(40, 40, 1.0f, 1.0f, 1.0f);
////            auto bits = cartridge->get_logo_bitmap();
////            for (int i = 0; i < 8; ++i) {
////                for (int j = 0; j < 48; ++j) {
////                    if (!bits[i][j]) continue;
////                    screen.SetPixel(j + 50, (7 - i) + 75, 1.0f, 1.0f, 1.0f);
////                }
////            }
//            glBindBuffer(GL_ARRAY_BUFFER, VBO);
//            void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//            if (ptr) {
//                // 更新数据
//                memcpy(ptr, screen.vertices_, sizeof(screen.vertices_));
//                // 取消映射
//                glUnmapBuffer(GL_ARRAY_BUFFER);
//            }
//        }

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, pixelsLen);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
