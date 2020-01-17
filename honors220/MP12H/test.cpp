#include<iostream>
#include<stdio.h>
#include<string.h>

int main()
{
    char buf[] = {"  color   0x110   "};
    char *ptr;
    char trailing[2]
    int conversion = sscanf(buf, "%*[ ]%s%*[ ]", ptr);
    std::cout << conversion <<std::endl << ptr << std::endl;
    conversion = sscanf(buf, "%*s%*[ ]%X%1s", x, trailing[2]);
    std::cout << conversion << std::endl << x << std::endl;
    return 1;
}
