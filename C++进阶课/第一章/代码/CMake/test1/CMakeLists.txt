
# 设置最小版本支持
cmake_minimum_required(VERSION 2.8)         

# 项目名称
project(HELLO)

# 生成可执行程序,依赖于hello.cpp生成hello可执行程序
add_executable(hello_cmake hello.cpp)