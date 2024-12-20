#pragma once

#include <glad/glad.h>

#include <string>

class Shader {
public:
  // 程序ID
  unsigned int shaderId_ = 0;
public:
  // 构造器读取并构建着色器
  Shader(const char* vertexPath, const char* fragmentPath);
  // 使用/激活程序
  void use() const;
  // uniform工具函数
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};
