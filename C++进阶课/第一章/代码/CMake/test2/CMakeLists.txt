# 指定最小编译版本
cmake_minimum_required(VERSION 2.8)

# 执行工程名称
project(SWAP)

# 指定头文件路径  就是 g++ 编译器的 -I 选项
include_directories(include)

# 生成可执行程序
add_executable(swap_cmake main.cpp src/swap.cpp)