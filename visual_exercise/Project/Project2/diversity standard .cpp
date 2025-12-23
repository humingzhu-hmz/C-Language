// #include <stdio.h>
// #include <windows.h>
// //ANSI American National Stdandards Institute �������ұ�׼Э��
// void enable_ansi() {
//    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    DWORD mode = 0;
//    GetConsoleMode(hOut, &mode);
//    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//    SetConsoleMode(hOut, mode);
// }

// int main() {
//    enable_ansi();

//    // ǰ��ɫ
//    printf("\033[30m��ɫǰ��\033[0m\n"); 
//    printf("\033[31m��ɫǰ��\033[0m\n");
//    printf("\033[32m��ɫǰ��\033[0m\n");
//    printf("\033[33m��ɫǰ��\033[0m\n");
//    printf("\033[34m��ɫǰ��\033[0m\n");
//    printf("\033[35m��ɫǰ��\033[0m\n");
//    printf("\033[36m��ɫǰ��\033[0m\n");
//    printf("\033[37m��ɫǰ��\033[0m\n");

//    // ����ɫ
//    printf("\033[40;34m���ֺڱ���\033[0m\n");
//    printf("\033[41m��ɫ����\033[0m\n");
//    printf("\033[42m��ɫ����\033[0m\n");
//    printf("\033[43m��ɫ����\033[0m\n");
//    printf("\033[44m��ɫ����\033[0m\n");
//    printf("\033[45m��ɫ����\033[0m\n");
//    printf("\033[46m��ɫ����\033[0m\n");
//    printf("\033[47m��ɫ����\033[0m\n");

//    // ��ϣ�ǰ��ɫ�ͱ���ɫ
//    printf("\033[31;42m�����̱���\033[0m\n");
//    printf("\033[33;44m����������\033[0m\n");

//    // ������ʽ
//    printf("\033[1;31m�����ɫ\033[0m\n");
//    printf("\033[4;32m�»�����ɫ\033[0m\n");
//    printf("\033[1;4;33m�����»��߻�ɫ\033[0m\n");

//    return 0;
// }