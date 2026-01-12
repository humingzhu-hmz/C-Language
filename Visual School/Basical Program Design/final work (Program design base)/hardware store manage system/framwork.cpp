#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ==================== 角色 ==================== */
typedef enum { ADMIN, EMPLOYEE } Role;

/* ==================== 用户结构 ==================== */
// -------------------- 用户结构 --------------------
typedef struct {
    int id;
    char name[30];
    char password[20];
    Role role;
} User;

User currentUser; // 当前登录用户

/* ==================== 产品结构 ==================== */
// -------------------- 产品结构 --------------------
typedef struct {
    int id;
    char name[50];
    int stock;
    double price;
} Product;

/* ==================== 销售结构 ==================== */
// -------------------- 销售结构 --------------------
typedef struct {
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Sale;

/* ==================== 退货结构 ==================== */
// -------------------- 退货结构 --------------------
typedef struct {
    int returnId;
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Return;

/* ==================== 状态 ==================== */
// -------------------- 状态 --------------------
typedef enum {
    STATE_LOGIN,
    STATE_ADMIN_MENU,
    STATE_ADMIN_PRODUCT_MENU,
    STATE_ADMIN_USER_MENU,
    STATE_ADMIN_STAT_MENU,
    STATE_ADMIN_RETURN_MENU,
    STATE_EMPLOYEE_MENU,
    STATE_EMPLOYEE_SALE_MENU,
    STATE_EMPLOYEE_PASSWORD_MENU,
    STATE_EXIT
} State;

State currentState;

/* ==================== 状态转移动作 ==================== */
// -------------------- 状态转移动作 --------------------
typedef enum {
    NAV_NONE,
    NAV_LOGIN_SUCCESS,
    NAV_ENTER_PRODUCT_MENU,
    NAV_ENTER_USER_MENU,
    NAV_ENTER_STAT_MENU,
    NAV_ENTER_RETURN_MENU,
    NAV_ENTER_SALE_MENU,
    NAV_ENTER_PASSWORD_MENU,
    NAV_BACK,
    NAV_EXIT
} NavAction;

/* ==================== 业务动作 ==================== */
// -------------------- 业务动作 --------------------
typedef enum {
    FUNC_NONE,

    FUNC_PRODUCT_ADD,
    FUNC_PRODUCT_DELETE,
    FUNC_PRODUCT_UPDATE,
    FUNC_PRODUCT_QUERY,
    FUNC_PRODUCT_LIST,

    FUNC_USER_ADD,
    FUNC_USER_DELETE,
    FUNC_USER_RESET,

    FUNC_SALE_PRODUCT,
    FUNC_CHECK_SALES,

    FUNC_RETURN_PRODUCT,
    FUNC_STAT_TOP5,
    FUNC_STAT_MONTHLY,
    FUNC_CHECK_STOCK_WARNING
} FuncAction;

/* ==================== 输入动作 ==================== */
// -------------------- 输入动作 --------------------
typedef struct {
    NavAction nav;
    FuncAction func;
} InputAction;

/* ==================== 功能函数 ==================== */
// -------------------- 功能函数 --------------------
void product_add() { printf("[添加商品]\n"); }
void product_delete() { printf("[删除商品]\n"); }
void product_update() { printf("[修改商品]\n"); }
void product_query() { printf("[查询商品]\n"); }
void product_list() { printf("[浏览商品]\n"); }

void user_add() { printf("[添加员工]\n"); }
void user_delete() { printf("[删除员工]\n"); }
void user_reset_password() { printf("[重置密码]\n"); }

void sale_product() { printf("[销售商品]\n"); }
void check_sales() { printf("[查询销售]\n"); }
void stat_monthly() { printf("[月销售统计]\n"); }
void stat_top5() { printf("[热销Top5]\n"); }
void check_stock_warning() { printf("[库存预警]\n"); }

void return_product() { printf("[退货登记]\n"); }

/* ==================== 状态机调度 ==================== */
// -------------------- 状态机调度 --------------------
void dispatch(NavAction nav) {
    switch (currentState) {

    case STATE_LOGIN:
        if (nav == NAV_LOGIN_SUCCESS) {
            currentState = (currentUser.role == ADMIN)
                ? STATE_ADMIN_MENU
                : STATE_EMPLOYEE_MENU;
        }
        else if (nav == NAV_EXIT) {
            currentState = STATE_EXIT;
        }
        break;

    case STATE_ADMIN_MENU:
        if (nav == NAV_ENTER_PRODUCT_MENU) currentState = STATE_ADMIN_PRODUCT_MENU;
        else if (nav == NAV_ENTER_USER_MENU) currentState = STATE_ADMIN_USER_MENU;
        else if (nav == NAV_ENTER_STAT_MENU) currentState = STATE_ADMIN_STAT_MENU;
        else if (nav == NAV_ENTER_RETURN_MENU) currentState = STATE_ADMIN_RETURN_MENU;
        else if (nav == NAV_EXIT) currentState = STATE_EXIT;
        break;

    case STATE_EMPLOYEE_MENU:
        if (nav == NAV_ENTER_SALE_MENU) currentState = STATE_EMPLOYEE_SALE_MENU;
        else if (nav == NAV_ENTER_PASSWORD_MENU) currentState = STATE_EMPLOYEE_PASSWORD_MENU;
        else if (nav == NAV_EXIT) currentState = STATE_EXIT;
        break;

    case STATE_ADMIN_PRODUCT_MENU:
    case STATE_ADMIN_USER_MENU:
    case STATE_ADMIN_STAT_MENU:
    case STATE_ADMIN_RETURN_MENU:
    case STATE_EMPLOYEE_SALE_MENU:
    case STATE_EMPLOYEE_PASSWORD_MENU:
        if (nav == NAV_BACK) {
            currentState = (currentUser.role == ADMIN)
                ? STATE_ADMIN_MENU
                : STATE_EMPLOYEE_MENU;
        }
        break;

    default:
        break;
    }
}

/* ==================== 菜单显示 ==================== */
// -------------------- 菜单显示 --------------------
void showMenu() {
    switch (currentState) {
    case STATE_LOGIN:
        printf("=== 登录 ===\n1. 登录\n0. 退出\n");
        break;
    case STATE_ADMIN_MENU:
        printf("=== 管理员菜单 ===\n1. 产品管理\n2. 人员管理\n3. 销售统计\n4. 退货管理\n0. 退出\n");
        break;
    case STATE_ADMIN_PRODUCT_MENU:
        printf("=== 产品管理 ===\n1. 添加\n2. 删除\n3. 修改\n4. 查询\n5. 浏览\n0. 返回\n");
        break;
    case STATE_ADMIN_USER_MENU:
        printf("=== 人员管理 ===\n1. 添加\n2. 删除\n3. 重置密码\n0. 返回\n");
        break;
    case STATE_ADMIN_STAT_MENU:
        printf("=== 销售统计 ===\n1. 查询销售\n2. 月统计\n3. Top5\n4. 库存预警\n0. 返回\n");
        break;
    case STATE_ADMIN_RETURN_MENU:
        printf("=== 退货管理 ===\n1. 退货登记\n2. 查询退货\n0. 返回\n");
        break;
    case STATE_EMPLOYEE_MENU:
        printf("=== 员工菜单 ===\n1. 销售\n2. 修改密码\n0. 退出\n");
        break;
    case STATE_EMPLOYEE_SALE_MENU:
        printf("=== 销售菜单 ===\n1. 销售商品\n0. 返回\n");
        break;
    case STATE_EMPLOYEE_PASSWORD_MENU:
        printf("=== 密码管理 ===\n1. 修改密码\n0. 返回\n");
        break;
    default:
        break;
    }
}

/* ==================== 输入解析 ==================== */
// -------------------- 输入解析 --------------------
InputAction getActionFromInput() {
    InputAction a = { NAV_NONE, FUNC_NONE };
    int choice;
    scanf("%d", &choice);

    switch (currentState) {

    case STATE_LOGIN:
        if (choice == 1) a.nav = NAV_LOGIN_SUCCESS;
        else if (choice == 0) a.nav = NAV_EXIT;
        break;

    case STATE_ADMIN_MENU:
        if (choice == 1) a.nav = NAV_ENTER_PRODUCT_MENU;
        else if (choice == 2) a.nav = NAV_ENTER_USER_MENU;
        else if (choice == 3) a.nav = NAV_ENTER_STAT_MENU;
        else if (choice == 4) a.nav = NAV_ENTER_RETURN_MENU;
        else if (choice == 0) a.nav = NAV_EXIT;
        break;

    case STATE_ADMIN_PRODUCT_MENU:
        if (choice == 1) a.func = FUNC_PRODUCT_ADD;
        else if (choice == 2) a.func = FUNC_PRODUCT_DELETE;
        else if (choice == 3) a.func = FUNC_PRODUCT_UPDATE;
        else if (choice == 4) a.func = FUNC_PRODUCT_QUERY;
        else if (choice == 5) a.func = FUNC_PRODUCT_LIST;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    case STATE_ADMIN_USER_MENU:
        if (choice == 1) a.func = FUNC_USER_ADD;
        else if (choice == 2) a.func = FUNC_USER_DELETE;
        else if (choice == 3) a.func = FUNC_USER_RESET;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    case STATE_ADMIN_STAT_MENU:
        if (choice == 1) a.func = FUNC_CHECK_SALES;
        else if (choice == 2) a.func = FUNC_STAT_MONTHLY;
        else if (choice == 3) a.func = FUNC_STAT_TOP5;
        else if (choice == 4) a.func = FUNC_CHECK_STOCK_WARNING;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    case STATE_ADMIN_RETURN_MENU:
        if (choice == 1) a.func = FUNC_RETURN_PRODUCT;
        else if (choice == 2) a.func = FUNC_CHECK_SALES;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    case STATE_EMPLOYEE_MENU:
        if (choice == 1) a.nav = NAV_ENTER_SALE_MENU;
        else if (choice == 2) a.nav = NAV_ENTER_PASSWORD_MENU;
        else if (choice == 0) a.nav = NAV_EXIT;
        break;

    case STATE_EMPLOYEE_SALE_MENU:
        if (choice == 1) a.func = FUNC_SALE_PRODUCT;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    case STATE_EMPLOYEE_PASSWORD_MENU:
        if (choice == 1) a.func = FUNC_USER_RESET;
        else if (choice == 0) a.nav = NAV_BACK;
        break;

    default:
        break;
    }

    return a;
}

/* ==================== 主函数 ==================== */
// -------------------- 主函数 --------------------
int main() {
    currentUser.role = ADMIN;
    strcpy(currentUser.name, "admin");

    currentState = STATE_LOGIN;

    while (currentState != STATE_EXIT) {
        showMenu();

        InputAction a = getActionFromInput();

        switch (a.func) {
        case FUNC_PRODUCT_ADD: product_add(); break;
        case FUNC_PRODUCT_DELETE: product_delete(); break;
        case FUNC_PRODUCT_UPDATE: product_update(); break;
        case FUNC_PRODUCT_QUERY: product_query(); break;
        case FUNC_PRODUCT_LIST: product_list(); break;

        case FUNC_USER_ADD: user_add(); break;
        case FUNC_USER_DELETE: user_delete(); break;
        case FUNC_USER_RESET: user_reset_password(); break;

        case FUNC_SALE_PRODUCT: sale_product(); break;
        case FUNC_CHECK_SALES: check_sales(); break;
        case FUNC_STAT_MONTHLY: stat_monthly(); break;
        case FUNC_STAT_TOP5: stat_top5(); break;
        case FUNC_CHECK_STOCK_WARNING: check_stock_warning(); break;

        case FUNC_RETURN_PRODUCT: return_product(); break;
        default: break;
        }

        dispatch(a.nav);
    }

    printf("系统已退出。\n");
    return 0;
}
