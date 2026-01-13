#include "framework.h"

int main() {
    // sample init
    User a = { 0 }; strcpy(a.id, "admin"); strcpy(a.name, "管理员"); strcpy(a.password, "admin"); a.role = ADMIN; users[userCount++] = a;
    User b = { 0 }; strcpy(b.id, "emp1"); strcpy(b.name, "员工A"); strcpy(b.password, "1234"); b.role = EMPLOYEE; users[userCount++] = b;

    Product p;
    memset(&p, 0, sizeof(p)); strcpy(p.id, "101"); strcpy(p.name, "苹果"); p.stock = 50; p.price = 3.5; products[productCount++] = p;
    StockRecord sr; sr.recordId = nextStockRecordId++; sr.productId = atoi(p.id); sr.quantityAdded = p.stock; time_t t = time(NULL); strftime(sr.date, sizeof(sr.date), "%Y-%m-%d %H:%M:%S", localtime(&t)); stockRecords[stockRecordCount++] = sr;
    memset(&p, 0, sizeof(p)); strcpy(p.id, "102"); strcpy(p.name, "香蕉"); p.stock = 30; p.price = 2.0; products[productCount++] = p; sr.recordId = nextStockRecordId++; sr.productId = atoi(p.id); sr.quantityAdded = p.stock; time_t t2 = time(NULL); strftime(sr.date, sizeof(sr.date), "%Y-%m-%d %H:%M:%S", localtime(&t2)); stockRecords[stockRecordCount++] = sr;
    memset(&p, 0, sizeof(p)); strcpy(p.id, "103"); strcpy(p.name, "橙子"); p.stock = 0; p.price = 4.0; products[productCount++] = p; sr.recordId = nextStockRecordId++; sr.productId = atoi(p.id); sr.quantityAdded = p.stock; time_t t3 = time(NULL); strftime(sr.date, sizeof(sr.date), "%Y-%m-%d %H:%M:%S", localtime(&t3)); stockRecords[stockRecordCount++] = sr;

    ShowWelcomeScreen();
    currentState = STATE_LOGIN;
    while (currentState != STATE_EXIT) {
        Showmenu();
        InputAction act = Getactionfrominput();
        if (act.nav != NAV_NONE) Dispatch(act.nav);
        if (act.func != FUNC_NONE) Executing(act.func);
    }

    printf("是否保存数据? (y/n): ");
    char c; if (scanf(" %c", &c) == 1 && (c == 'y' || c == 'Y')) { product_save(); user_save(); }
    printf("再见。\n");
    return 0;
}
