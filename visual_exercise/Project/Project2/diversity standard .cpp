#include <stdio.h>
#include <windows.h>
//ANSI American National Stdandards Institute 美国国家标准协会
void enable_ansi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}

int main() {
    enable_ansi();

    // 前景色
    printf("\033[30m黑色前景\033[0m\n"); 
    printf("\033[31m红色前景\033[0m\n");
    printf("\033[32m绿色前景\033[0m\n");
    printf("\033[33m黄色前景\033[0m\n");
    printf("\033[34m蓝色前景\033[0m\n");
    printf("\033[35m紫色前景\033[0m\n");
    printf("\033[36m青色前景\033[0m\n");
    printf("\033[37m白色前景\033[0m\n");

    // 背景色
    printf("\033[40;34m蓝字黑背景\033[0m\n");
    printf("\033[41m红色背景\033[0m\n");
    printf("\033[42m绿色背景\033[0m\n");
    printf("\033[43m黄色背景\033[0m\n");
    printf("\033[44m蓝色背景\033[0m\n");
    printf("\033[45m紫色背景\033[0m\n");
    printf("\033[46m青色背景\033[0m\n");
    printf("\033[47m白色背景\033[0m\n");

    // 组合：前景色和背景色
    printf("\033[31;42m红字绿背景\033[0m\n");
    printf("\033[33;44m黄字蓝背景\033[0m\n");

    // 加上样式
    printf("\033[1;31m粗体红色\033[0m\n");
    printf("\033[4;32m下划线绿色\033[0m\n");
    printf("\033[1;4;33m粗体下划线黄色\033[0m\n");

    return 0;
}