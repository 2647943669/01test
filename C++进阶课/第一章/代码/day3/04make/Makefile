
var1 = main.o          #定义一个变量并赋值
var1 += operator.o #给变量追加值

#条件选择，如果变量COMPILE的值是g++那么CC的值就是g++，否则是gcc
ifeq ($(COMPILE), g++)
	CC:=g++
else
	CC:=gcc
endif


#第一个依赖关系
all:operator

operator:$(var1)
#	g++ main.o operator.o -o operator
	$(CC) $^ -o $@

#main.o:main.cpp
#	g++ -c $< -o $@
#operator.o:operator.cpp
#	g++ -c $^ -o $@
#将上述两个规则统一成一个规则

#此时的%表示所有的Makefile内容，不能换成*
%.o:%.cpp
	$(CC) -c $< -o $@



clean:
	rm -f *.o operator          #此处的*是普通通配符

