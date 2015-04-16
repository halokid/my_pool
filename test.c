#include <stdio.h>


void p_str(char *str)
{
	printf("%s\n", str);
}

void p_str2(char str[])
{
	printf("%s\n", str);
}

int main()
{
	char *s;
	s = "select user from user";
	p_str(s);


	//char a[100];
	//char a[];	

//如果用上面这句， 编译时会产生错误 test.c:22: error: incompatible types when assigning to type ‘char[100]’ from type ‘char *这类的错误， 因为定义一个数组就是定义一块内存块，如果你没有用一些东西去初始化这个变量，那么C语言就会把你定义的这个变量视为一个指向数组的指针，你给指针定义一个长度是会产生错误的

	char a[100] = "select test from test";
	//a = "select test from test";
	p_str2(a);
}
