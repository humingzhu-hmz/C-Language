#include "framework.h"

/* ================== 基础控制 ================== */

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearScreen() {
    system("cls");
}

/* ================== 通用绘制 ================== */

void DrawMenuBox(int width, int height) {
    printf("+");
    for (int i = 0; i < width - 2; i++) printf("=");
    printf("+\n");

    for (int i = 0; i < height - 2; i++) {
        printf("|");
        for (int j = 0; j < width - 2; j++) printf(" ");
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < width - 2; i++) printf("=");
    printf("+\n");
}

void PrintCentered(int width, const char* text) {
    int len = (int)strlen(text);
    int pad = (width - 2 - len) / 2;
    printf("|");
    for (int i = 0; i < pad; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < width - 2 - pad - len; i++) printf(" ");
    printf("|\n");
}

/* ================== 欢迎界面 ================== */

void ShowWelcomeScreen() {
    ClearScreen();
    SetColor(11);

    DrawMenuBox(60, 10);
    PrintCentered(60, "WELCOME TO HARDWARE STORE SYSTEM");
    PrintCentered(60, "");
    PrintCentered(60, "Course Design Project");
    PrintCentered(60, "Press any key to continue...");

    SetColor(7);
    _getch();
}

/* ================== 密码隐藏输入 ================== */

void HidePassword(char* password) {
    char ch;
    int idx = 0;

    while (1) {
        ch = _getch();

        if (ch == '\r') {          // Enter
            password[idx] = '\0';
            printf("\n");
            break;
        }
        else if (ch == '\b') {     // Backspace
            if (idx > 0) {
                idx--;
                printf("\b \b");
            }
        }
        else if (idx < 19) {
            password[idx++] = ch;
            printf("*");
        }
    }
}

/* ================== 文件路径 ================== */

char* Filelocation(const char* filename) {
    static char path[512];
    sprintf(path, "%s\\%s", Workspace, filename);
    return path;
}

/* ================== 菜单显示 ================== */

void Showmenu() {
    ClearScreen();
    SetColor(14);

    DrawMenuBox(60, 18);

    SetColor(11);

    switch (currentState) {

    case STATE_LOGIN:
        PrintCentered(60, "LOGIN MENU");
        PrintCentered(60, "");
        PrintCentered(60, "1. Login");
        PrintCentered(60, "2. Exit");
        break;

    case STATE_ADMIN_MENU:
        PrintCentered(60, "ADMIN MAIN MENU");
        PrintCentered(60, "");
        PrintCentered(60, "1. Product Management");
        PrintCentered(60, "2. User Management");
        PrintCentered(60, "3. Statistics");
        PrintCentered(60, "4. Return Management");
        PrintCentered(60, "5. Logout");
        break;

    case STATE_ADMIN_PRODUCT_MENU:
        PrintCentered(60, "PRODUCT MANAGEMENT");
        PrintCentered(60, "");
        PrintCentered(60, "1. Add Product");
        PrintCentered(60, "2. Delete Product");
        PrintCentered(60, "3. Update Product");
        PrintCentered(60, "4. Query Product");
        PrintCentered(60, "5. List Products");
        PrintCentered(60, "6. Save Products");
        PrintCentered(60, "7. Back");
        break;

    case STATE_ADMIN_USER_MENU:
        PrintCentered(60, "USER MANAGEMENT");
        PrintCentered(60, "");
        PrintCentered(60, "1. Add User");
        PrintCentered(60, "2. Delete User");
        PrintCentered(60, "3. Update User");
        PrintCentered(60, "4. Query User");
        PrintCentered(60, "5. Save Users");
        PrintCentered(60, "6. Reset Password");
        PrintCentered(60, "7. Back");
        break;

    case STATE_EMPLOYEE_MENU:
        PrintCentered(60, "EMPLOYEE MENU");
        PrintCentered(60, "");
        PrintCentered(60, "1. Sell Product");
        PrintCentered(60, "2. Query Product");
        PrintCentered(60, "3. Product List");
        PrintCentered(60, "4. Logout");
        break;

    default:
        PrintCentered(60, "UNKNOWN STATE");
        break;
    }

    SetColor(7);
}

/* ================== 输入解析 ================== */

InputAction Getactionfrominput() {
    InputAction act;
    act.nav = NAV_NONE;
    act.func = FUNC_NONE;

    int choice;
    printf("\nSelect: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return act;
    }

    switch (currentState) {

    case STATE_LOGIN:
        if (choice == 1) {
            char id[15], pwd[20];
            printf("User ID: ");
            scanf("%14s", id);
            printf("Password: ");
            HidePassword(pwd);

            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i].id, id) == 0 &&
                    strcmp(users[i].password, pwd) == 0) {
                    currentUser = users[i];
                    act.nav = NAV_LOGIN_SUCCESS;
                    return act;
                }
            }
            printf("Login failed.\n");
            system("pause");
        }
        else if (choice == 2) {
            act.nav = NAV_EXIT;
        }
        break;

    case STATE_ADMIN_MENU:
        if (choice == 1) act.nav = NAV_ENTER_PRODUCT_MENU;
        else if (choice == 2) act.nav = NAV_ENTER_USER_MENU;
        else if (choice == 3) act.nav = NAV_ENTER_STAT_MENU;
        else if (choice == 4) act.nav = NAV_ENTER_RETURN_MENU;
        else if (choice == 5) act.nav = NAV_EXIT;
        break;

    case STATE_ADMIN_PRODUCT_MENU:
        if (choice == 1) act.func = FUNC_PRODUCT_ADD;
        else if (choice == 2) act.func = FUNC_PRODUCT_DELETE;
        else if (choice == 3) act.func = FUNC_PRODUCT_UPDATE;
        else if (choice == 4) act.func = FUNC_PRODUCT_QUERY;
        else if (choice == 5) act.func = FUNC_PRODUCT_LIST;
        else if (choice == 6) act.func = FUNC_PRODUCT_SAVE;
        else if (choice == 7) act.nav = NAV_BACK;
        break;

    case STATE_ADMIN_USER_MENU:
        if (choice == 1) act.func = FUNC_USER_ADD;
        else if (choice == 2) act.func = FUNC_USER_DELETE;
        else if (choice == 3) act.func = FUNC_USER_UPDATE;
        else if (choice == 4) act.func = FUNC_USER_QUERY;
        else if (choice == 5) act.func = FUNC_USER_SAVE;
        else if (choice == 6) act.func = FUNC_USER_RESET;
        else if (choice == 7) act.nav = NAV_BACK;
        break;

    case STATE_EMPLOYEE_MENU:
        if (choice == 1) act.func = FUNC_SALE_PRODUCT;
        else if (choice == 2) act.func = FUNC_PRODUCT_QUERY;
        else if (choice == 3) act.func = FUNC_PRODUCT_LIST;
        else if (choice == 4) act.nav = NAV_EXIT;
        break;

    default:
        break;
    }

    return act;
}

/* ================== 状态分发 ================== */

void Dispatch(NavAction nav) {
    switch (nav) {
    case NAV_LOGIN_SUCCESS:
        currentState = (currentUser.role == ADMIN)
            ? STATE_ADMIN_MENU
            : STATE_EMPLOYEE_MENU;
        break;
    case NAV_ENTER_PRODUCT_MENU:
        currentState = STATE_ADMIN_PRODUCT_MENU;
        break;
    case NAV_ENTER_USER_MENU:
        currentState = STATE_ADMIN_USER_MENU;
        break;
    case NAV_BACK:
        currentState = (currentUser.role == ADMIN)
            ? STATE_ADMIN_MENU
            : STATE_EMPLOYEE_MENU;
        break;
    case NAV_EXIT:
        currentState = STATE_EXIT;
        ISRUNNING = false;
        break;
    default:
        break;
    }
}

/* ================== 功能执行 ================== */

void Executing(FuncAction func) {
    switch (func) {
    case FUNC_PRODUCT_ADD: product_add(); break;
    case FUNC_PRODUCT_DELETE: product_delete(); break;
    case FUNC_PRODUCT_UPDATE: product_update(); break;
    case FUNC_PRODUCT_QUERY: product_query(); break;
    case FUNC_PRODUCT_LIST: product_list(); break;
    case FUNC_PRODUCT_SAVE: product_save(); break;

    case FUNC_USER_ADD: user_add(); break;
    case FUNC_USER_DELETE: user_delete(); break;
    case FUNC_USER_UPDATE: user_update(); break;
    case FUNC_USER_QUERY: user_query(); break;
    case FUNC_USER_SAVE: user_save(); break;
    case FUNC_USER_RESET: user_reset_password(); break;

    case FUNC_SALE_PRODUCT: sale_product(); break;
    case FUNC_CHECK_SALES: check_sales(); break;

    default:
        printf("Function not implemented.\n");
        system("pause");
        break;
    }
}
