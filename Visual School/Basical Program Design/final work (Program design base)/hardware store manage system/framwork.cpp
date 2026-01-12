#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { ADMIN, EMPLOYEE } Role;

// -------------------- 用户结构 --------------------
typedef struct {
    int id;
    char name[30];
    char password[20];
    Role role;
} User;

User currentUser; // 当前登录用户

// -------------------- 产品结构 --------------------
typedef struct {
    int id;
    char name[50];
    int stock;
    double price;
} Product;

// -------------------- 销售结构 --------------------
typedef struct {
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Sale;

// -------------------- 退货结构 --------------------
typedef struct {
    int returnId;
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Return;

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

// -------------------- 动作 --------------------
typedef enum {
    ACTION_NONE,
    ACTION_LOGIN_SUCCESS,
    ACTION_ENTER_ADMIN_MENU,
    ACTION_ENTER_EMPLOYEE_MENU,
    ACTION_ENTER_PRODUCT_MENU,
    ACTION_ENTER_USER_MENU,
    ACTION_ENTER_STAT_MENU,
    ACTION_ENTER_RETURN_MENU,
    ACTION_ENTER_SALE_MENU,
    ACTION_ENTER_PASSWORD_MENU,
    ACTION_BACK,
    ACTION_EXIT,

    // 功能动作
    ACTION_PRODUCT_ADD,
    ACTION_PRODUCT_DELETE,
    ACTION_PRODUCT_UPDATE,
    ACTION_PRODUCT_QUERY,
    ACTION_PRODUCT_LIST,

    ACTION_USER_ADD,
    ACTION_USER_DELETE,
    ACTION_USER_RESET,

    ACTION_SALE_PRODUCT,
    ACTION_CHECK_SALES,

    ACTION_RETURN_PRODUCT,
    ACTION_STAT_TOP5,
    ACTION_STAT_MONTHLY,
    ACTION_CHECK_STOCK_WARNING
} Action;

// -------------------- 功能函数（先用printf模拟） --------------------
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

// -------------------- 状态机调度器 --------------------
void dispatch(Action action) {
    switch (currentState){
    case STATE_LOGIN:
        if (action == ACTION_LOGIN_SUCCESS) {
            if (currentUser.role == ADMIN)
                currentState = STATE_ADMIN_MENU;
            else
                currentState = STATE_EMPLOYEE_MENU;
        }
        else if (action == ACTION_EXIT)
            currentState = STATE_EXIT;
        break;

    case STATE_ADMIN_MENU:
        if (action == ACTION_ENTER_PRODUCT_MENU) currentState = STATE_ADMIN_PRODUCT_MENU;
        else if (action == ACTION_ENTER_USER_MENU) currentState = STATE_ADMIN_USER_MENU;
        else if (action == ACTION_ENTER_STAT_MENU) currentState = STATE_ADMIN_STAT_MENU;
        else if (action == ACTION_ENTER_RETURN_MENU) currentState = STATE_ADMIN_RETURN_MENU;
        else if (action == ACTION_EXIT) currentState = STATE_EXIT;
        break;

    case STATE_EMPLOYEE_MENU:
        if (action == ACTION_ENTER_SALE_MENU) currentState = STATE_EMPLOYEE_SALE_MENU;
        else if (action == ACTION_ENTER_PASSWORD_MENU) currentState = STATE_EMPLOYEE_PASSWORD_MENU;
        else if (action == ACTION_EXIT) currentState = STATE_EXIT;
        break;

    case STATE_ADMIN_PRODUCT_MENU:
    case STATE_ADMIN_USER_MENU:
    case STATE_ADMIN_STAT_MENU:
    case STATE_ADMIN_RETURN_MENU:
    case STATE_EMPLOYEE_SALE_MENU:
    case STATE_EMPLOYEE_PASSWORD_MENU:
        if (action == ACTION_BACK) {
            currentState = (currentUser.role == ADMIN) ? STATE_ADMIN_MENU : STATE_EMPLOYEE_MENU;
        }
        break;
    }
}

// -------------------- 菜单显示 --------------------
void showMenu() {
    switch (currentState) {
    case STATE_LOGIN:
        printf("=== 登录 ===\n1. 登录\n0. 退出\n");
        break;

    case STATE_ADMIN_MENU:
        printf("=== 管理员主菜单 ===\n1. 产品管理\n2. 人员管理\n3. 销售统计\n4. 退货管理\n0. 退出\n");
        break;

    case STATE_ADMIN_PRODUCT_MENU:
        printf("=== 产品管理 ===\n1. 添加\n2. 删除\n3. 修改\n4. 查询\n5. 浏览\n0. 返回\n");
        break;

    case STATE_ADMIN_USER_MENU:
        printf("=== 人员管理 ===\n1. 添加\n2. 删除\n3. 重置密码\n0. 返回\n");
        break;

    case STATE_ADMIN_STAT_MENU:
        printf("=== 销售统计 ===\n1. 查询销售信息\n2. 月销售统计\n3. 热销Top5\n4. 库存预警\n0. 返回\n");
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
    }
}

// -------------------- 控制台输入 → Action --------------------
Action getActionFromInput() {
    int choice;
    scanf("%d", &choice);

    switch (currentState) {
    case STATE_LOGIN:
        if (choice == 1) return ACTION_LOGIN_SUCCESS;
        if (choice == 0) return ACTION_EXIT;
        break;

    case STATE_ADMIN_MENU:
        if (choice == 1) return ACTION_ENTER_PRODUCT_MENU;
        if (choice == 2) return ACTION_ENTER_USER_MENU;
        if (choice == 3) return ACTION_ENTER_STAT_MENU;
        if (choice == 4) return ACTION_ENTER_RETURN_MENU;
        if (choice == 0) return ACTION_EXIT;
        break;

    case STATE_ADMIN_PRODUCT_MENU:
        if (choice == 1) return ACTION_PRODUCT_ADD;
        if (choice == 2) return ACTION_PRODUCT_DELETE;
        if (choice == 3) return ACTION_PRODUCT_UPDATE;
        if (choice == 4) return ACTION_PRODUCT_QUERY;
        if (choice == 5) return ACTION_PRODUCT_LIST;
        if (choice == 0) return ACTION_BACK;
        break;

    case STATE_ADMIN_USER_MENU:
        if (choice == 1) return ACTION_USER_ADD;
        if (choice == 2) return ACTION_USER_DELETE;
        if (choice == 3) return ACTION_USER_RESET;
        if (choice == 0) return ACTION_BACK;
        break;

    case STATE_ADMIN_STAT_MENU:
        if (choice == 1) return ACTION_CHECK_SALES;
        if (choice == 2) return ACTION_STAT_MONTHLY;
        if (choice == 3) return ACTION_STAT_TOP5;
        if (choice == 4) return ACTION_CHECK_STOCK_WARNING;
        if (choice == 0) return ACTION_BACK;
        break;

    case STATE_ADMIN_RETURN_MENU:
        if (choice == 1) return ACTION_RETURN_PRODUCT;
        if (choice == 2) return ACTION_CHECK_SALES;
        if (choice == 0) return ACTION_BACK;
        break;

    case STATE_EMPLOYEE_MENU:
        if (choice == 1) return ACTION_ENTER_SALE_MENU;
        if (choice == 2) return ACTION_ENTER_PASSWORD_MENU;
        if (choice == 0) return ACTION_EXIT;
        break;

    case STATE_EMPLOYEE_SALE_MENU:
        if (choice == 1) return ACTION_SALE_PRODUCT;
        if (choice == 0) return ACTION_BACK;
        break;

    case STATE_EMPLOYEE_PASSWORD_MENU:
        if (choice == 1) return ACTION_USER_RESET;
        if (choice == 0) return ACTION_BACK;
        break;
    }
    return ACTION_NONE;
}

// -------------------- 主循环 --------------------
int main() {
    // 模拟登录用户，先写死为管理员
    currentUser.role = ADMIN;
    strcpy(currentUser.name, "admin");

    currentState = STATE_LOGIN;

    while (currentState != STATE_EXIT) {
        showMenu();
        Action action = getActionFromInput();
        /* dispatch(action);
        dispatch 仅仅当action作为改变状态的量才有作用,而不处理动作
        所以当action为动作的时候不会对currentState有影响
        但是这从逻辑架构上是大错误,应该先在当前状态处理动作在改变
        状态,因为switch只是对动作进行操作,
        即使action是状态变量也不会进行操作 
        但是如果将状态改变动作和操作动作分开是不是更好呢,如果对于一个同时
        改变状态和执行操作的action,那不是要在定义一个额外兼顾两者的变量
        还有修改switch结构,随着补丁越打越多,那太难看了
        应该将两者分开在操作,就如同这样,switch(操作),dispatch(状态改变)*/             

        // 执行功能模块
        switch (action) {
        case ACTION_PRODUCT_ADD: product_add(); break;
        case ACTION_PRODUCT_DELETE: product_delete(); break;
        case ACTION_PRODUCT_UPDATE: product_update(); break;
        case ACTION_PRODUCT_QUERY: product_query(); break;
        case ACTION_PRODUCT_LIST: product_list(); break;

        case ACTION_USER_ADD: user_add(); break;
        case ACTION_USER_DELETE: user_delete(); break;
        case ACTION_USER_RESET: user_reset_password(); break;

        case ACTION_SALE_PRODUCT: sale_product(); break;
        case ACTION_CHECK_SALES: check_sales(); break;
        case ACTION_STAT_MONTHLY: stat_monthly(); break;
        case ACTION_STAT_TOP5: stat_top5(); break;
        case ACTION_CHECK_STOCK_WARNING: check_stock_warning(); break;

        case ACTION_RETURN_PRODUCT: return_product(); break;

        default: break;
        }
        dispatch(action);
    }

    printf("系统已退出。\n");
    return 0;
}