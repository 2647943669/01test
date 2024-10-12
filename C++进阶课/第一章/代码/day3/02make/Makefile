
#仅仅只有目标和依赖，没有命令
all:hello

# Makefile中的注释是以#开头
# 语法格式：
# 目标：依赖
#	通过依赖生成目标的指令
# 注意：指令前面必须使用同一个tab键隔开，不能使用多个空格顶过来

hello:hello.o
#g++ hello.o -o hello
	g++ $< -o $@

hello.o:hello.cpp
	g++ -c $< -o $@

# 此处一个规则是没有依赖，只有目标和指令
.PHONY:clean
clean distclean:
	rm  hello.o hello
