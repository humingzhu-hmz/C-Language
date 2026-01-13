#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define Workspace "E:\\desktop\\Program_and_code\\C-Language-Files\\Visual School\\Basical Program Design\\final work (Program design base)\\Text"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

// limits
#define MAX_PRODUCTS 200
#define MAX_SALES 1000
#define MAX_RETURNS 500
#define MAX_USERS 50
#define MAX_STOCK_RECORDS 500

typedef enum { ADMIN, EMPLOYEE } Role;

typedef struct {
    char id[15];
    char name[30];
    char password[20];
    Role role;
} User;

typedef struct {
    char id[15];
    char name[50];
    int stock;
    double price;
} Product;

typedef struct {
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Sale;

typedef struct {
    int returnId;
    int saleId;
    int productId;
    int quantity;
    char date[20];
} Return;

typedef struct {
    int recordId;
    int productId;
    int quantityAdded;
    char date[20];
} StockRecord;

typedef struct {
    Product product;
    int currentStock;
    int totalSold;
    int totalReturned;
    int totalAddedStock;
    Sale* sales;
    int saleCount;
    Return* returns;
    int returnCount;
    StockRecord* stockHistory;
    int stockHistoryCount;
    bool isNewlyAdded;
    bool isOutOfStock;
} ProductReport;

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

typedef enum {
    FUNC_NONE,
    FUNC_PRODUCT_ADD,
    FUNC_PRODUCT_DELETE,
    FUNC_PRODUCT_UPDATE,
    FUNC_PRODUCT_QUERY,
    FUNC_PRODUCT_LIST,
    FUNC_PRODUCT_SAVE,
    FUNC_USER_ADD,
    FUNC_USER_DELETE,
    FUNC_USER_UPDATE,
    FUNC_USER_QUERY,
    FUNC_USER_SAVE,
    FUNC_USER_RESET,
    FUNC_SALE_PRODUCT,
    FUNC_CHECK_SALES,
    FUNC_RETURN_PRODUCT,
    FUNC_RETURN_QUERY,
    FUNC_STAT_TOP5,
    FUNC_STAT_MONTHLY,
    FUNC_CHECK_STOCK_WARNING,
    FUNC_PRODUCT_REPORT
} FuncAction;

typedef struct {
    NavAction nav;
    FuncAction func;
} InputAction;

// globals (extern)
extern Product products[MAX_PRODUCTS];
extern int productCount;

extern Sale sales[MAX_SALES];
extern int saleCount;

extern Return returnsArr[MAX_RETURNS];
extern int returnCount;

extern StockRecord stockRecords[MAX_STOCK_RECORDS];
extern int stockRecordCount;

extern User users[MAX_USERS];
extern int userCount;

extern bool ISRUNNING;
extern User currentUser;
extern State currentState;

extern int nextSaleId;
extern int nextReturnId;
extern int nextStockRecordId;

// utility / UI
void SetColor(int color);
void ClearScreen();
void PrintBorder();
void DrawMenuBox(int width, int height, int left, int top);
void PrintCenteredInBox(int left, int top, int width, const char* s);
void HidePassword(char* password); // masked input with *
char* Filelocation(const char* filename);

// product functions
void product_add();
void product_delete();
void product_update();
void product_query();
void product_list();
void product_save();

// user functions
void user_add();
void user_delete();
void user_update();
void user_query();
void user_save();
void user_reset_password();

// sale / return / stats
void sale_product();
void check_sales();
void stat_monthly();
void stat_top5();
void check_stock_warning();
void return_product();
void return_query();

// reports
ProductReport query_product_report(const char* productId);
void free_product_report(ProductReport* r);

// state / UI loop
void Dispatch(NavAction nav);
void Executing(FuncAction func);
void Showmenu();
InputAction Getactionfrominput();
void ShowWelcomeScreen();
