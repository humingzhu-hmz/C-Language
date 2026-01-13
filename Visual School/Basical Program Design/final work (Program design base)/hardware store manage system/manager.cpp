#include "framework.h"

static int findProductIndexById(const char* id) {
    for (int i = 0; i < productCount; ++i) if (strcmp(products[i].id, id) == 0) return i;
    return -1;
}

void product_add() {
    if (productCount >= MAX_PRODUCTS) { printf("商品库已满。\n"); system("pause"); return; }
    Product p;
    memset(&p, 0, sizeof(p));
    printf("输入商品ID(数字字符串): ");
    scanf("%14s", p.id);
    if (findProductIndexById(p.id) != -1) { printf("该商品ID已存在。\n"); system("pause"); return; }
    printf("输入商品名称: ");
    while (getchar() != '\n');
    fgets(p.name, sizeof(p.name), stdin); p.name[strcspn(p.name, "\n")] = 0;
    printf("输入初始库存数量: ");
    if (scanf("%d", &p.stock) != 1) { printf("输入错误。\n"); system("pause"); return; }
    printf("输入价格: ");
    if (scanf("%lf", &p.price) != 1) { printf("输入错误。\n"); system("pause"); return; }
    products[productCount++] = p;
    if (stockRecordCount < MAX_STOCK_RECORDS) {
        StockRecord sr; sr.recordId = nextStockRecordId++; sr.productId = atoi(p.id); sr.quantityAdded = p.stock;
        time_t t = time(NULL); strftime(sr.date, sizeof(sr.date), "%Y-%m-%d %H:%M:%S", localtime(&t));
        stockRecords[stockRecordCount++] = sr;
    }
    printf("添加成功: %s (ID=%s)\n", p.name, p.id);
    system("pause");
}

void product_delete() {
    char id[16];
    printf("输入要删除的商品ID: "); scanf("%15s", id);
    int idx = findProductIndexById(id);
    if (idx == -1) { printf("未找到该商品。\n"); system("pause"); return; }
    for (int i = idx; i < productCount - 1; ++i) products[i] = products[i + 1];
    productCount--;
    printf("删除成功。\n"); system("pause");
}

void product_update() {
    char id[16];
    printf("输入要更新的商品ID: "); scanf("%15s", id);
    int idx = findProductIndexById(id);
    if (idx == -1) { printf("未找到该商品。\n"); system("pause"); return; }
    Product* p = &products[idx];
    printf("当前: 名称:%s 库存:%d 价格:%.2f\n", p->name, p->stock, p->price);
    printf("输入新名称(回车保留): "); while (getchar() != '\n');
    char tmp[64]; fgets(tmp, sizeof(tmp), stdin);
    if (tmp[0] != '\n') { tmp[strcspn(tmp, "\n")] = 0; strncpy(p->name, tmp, sizeof(p->name) - 1); }
    printf("输入调整库存(+/-/0): "); int delta; if (scanf("%d", &delta) == 1 && delta != 0) { p->stock += delta; if (delta > 0 && stockRecordCount < MAX_STOCK_RECORDS) { StockRecord sr; sr.recordId = nextStockRecordId++; sr.productId = atoi(p->id); sr.quantityAdded = delta; time_t t = time(NULL); strftime(sr.date, sizeof(sr.date), "%Y-%m-%d %H:%M:%S", localtime(&t)); stockRecords[stockRecordCount++] = sr; } }
    printf("输入新价格(0保留): "); double np; if (scanf("%lf", &np) == 1 && np > 0.0) p->price = np;
    printf("更新完成。\n"); system("pause");
}

void product_query() {
    char id[16];
    printf("输入要查询的商品ID: "); scanf("%15s", id);
    int idx = findProductIndexById(id);
    if (idx == -1) { printf("未找到商品 %s\n", id); system("pause"); return; }
    ProductReport r = query_product_report(id);
    printf("=== 商品报表 ===\n");
    printf("ID:%s 名称:%s\n", r.product.id, r.product.name);
    printf("当前库存:%d\n总销售:%d  总退货:%d  累计补货:%d\n", r.currentStock, r.totalSold, r.totalReturned, r.totalAddedStock);
    printf("状态: %s %s\n", r.isNewlyAdded ? "[NEW]" : "", r.isOutOfStock ? "[OUT]" : "");
    printf("\n-- 销售历史 --\n");
    for (int i = 0; i < r.saleCount; i++) printf("SaleID:%d Qty:%d Time:%s\n", r.sales[i].saleId, r.sales[i].quantity, r.sales[i].date);
    printf("\n-- 退货历史 --\n");
    for (int i = 0; i < r.returnCount; i++) printf("ReturnID:%d Qty:%d Time:%s\n", r.returns[i].returnId, r.returns[i].quantity, r.returns[i].date);
    printf("\n-- 补货历史 --\n");
    for (int i = 0; i < r.stockHistoryCount; i++) printf("StockRec:%d Added:%d Time:%s\n", r.stockHistory[i].recordId, r.stockHistory[i].quantityAdded, r.stockHistory[i].date);
    free_product_report(&r);
    system("pause");
}

void product_list() {
    printf("=== 商品列表 (%d) ===\n", productCount);
    for (int i = 0; i < productCount; i++) {
        Product* p = &products[i];
        char tag[64] = "";
        if (p->stock <= 0) strcat(tag, "[OUT]");
        int cnt = 0; for (int j = 0; j < stockRecordCount; j++) if (stockRecords[j].productId == atoi(p->id)) cnt++;
        if (cnt == 1) strcat(tag, "[NEW]");
        printf("ID:%s 名称:%s 库存:%d 价格:%.2f %s\n", p->id, p->name, p->stock, p->price, tag);
    }
    system("pause");
}

void product_save() {
    char path[512];
    FILE* f = fopen(Filelocation("products.txt"), "w");
    if (!f) { printf("保存失败。\n"); system("pause"); return; }
    for (int i = 0; i < productCount; i++) fprintf(f, "%s\t%s\t%d\t%.2f\n", products[i].id, products[i].name, products[i].stock, products[i].price);
    fclose(f);
    printf("保存完成。\n"); system("pause");
}

// user functions
static int findUserIndexById(const char* id) {
    for (int i = 0; i < userCount; i++) if (strcmp(users[i].id, id) == 0) return i;
    return -1;
}

void user_add() {
    if (userCount >= MAX_USERS) { printf("用户已满。\n"); system("pause"); return; }
    User u; memset(&u, 0, sizeof(u));
    printf("输入用户ID: "); scanf("%14s", u.id);
    if (findUserIndexById(u.id) != -1) { printf("用户已存在。\n"); system("pause"); return; }
    printf("输入用户名: "); while (getchar() != '\n'); fgets(u.name, sizeof(u.name), stdin); u.name[strcspn(u.name, "\n")] = 0;
    printf("输入密码: "); HidePassword(u.password);
    char confirm[20]; printf("确认密码: "); HidePassword(confirm);
    if (strcmp(u.password, confirm) != 0) { printf("两次密码不一致。\n"); system("pause"); return; }
    int r; printf("角色 (0=ADMIN,1=EMPLOYEE): "); if (scanf("%d", &r) != 1) r = 1; u.role = (r == 0 ? ADMIN : EMPLOYEE);
    users[userCount++] = u;
    printf("用户添加成功。\n"); system("pause");
}

void user_delete() {
    char id[16]; printf("输入要删除的用户ID: "); scanf("%15s", id);
    int idx = findUserIndexById(id);
    if (idx == -1) { printf("未找到用户。\n"); system("pause"); return; }
    for (int i = idx; i < userCount - 1; i++) users[i] = users[i + 1];
    userCount--; printf("删除完成。\n"); system("pause");
}

void user_update() {
    char id[16]; printf("输入要修改的用户ID: "); scanf("%15s", id);
    int idx = findUserIndexById(id); if (idx == -1) { printf("未找到用户。\n"); system("pause"); return; }
    User* u = &users[idx];
    printf("当前用户名:%s 角色:%d\n", u->name, u->role);
    printf("输入新用户名(回车保留): "); while (getchar() != '\n'); char tmp[64]; fgets(tmp, sizeof(tmp), stdin); if (tmp[0] != '\n') { tmp[strcspn(tmp, "\n")] = 0; strncpy(u->name, tmp, sizeof(u->name) - 1); }
    printf("输入新密码(空格保留): "); if (scanf("%19s", tmp) == 1) strncpy(u->password, tmp, sizeof(u->password) - 1);
    printf("修改完成。\n"); system("pause");
}

void user_query() {
    char id[16]; printf("输入用户ID: "); scanf("%15s", id);
    int idx = findUserIndexById(id); if (idx == -1) { printf("未找到用户。\n"); system("pause"); return; }
    printf("ID:%s 名称:%s 角色:%s\n", users[idx].id, users[idx].name, users[idx].role == ADMIN ? "ADMIN" : "EMPLOYEE"); system("pause");
}

void user_save() {
    FILE* f = fopen(Filelocation("users.txt"), "w");
    if (!f) { printf("无法保存用户。\n"); system("pause"); return; }
    for (int i = 0; i < userCount; i++) fprintf(f, "%s\t%s\t%s\t%d\n", users[i].id, users[i].name, users[i].password, users[i].role);
    fclose(f); printf("用户已保存。\n"); system("pause");
}

void user_reset_password() {
    char id[16]; printf("输入要重置密码的用户ID: "); scanf("%15s", id);
    int idx = findUserIndexById(id); if (idx == -1) { printf("未找到用户。\n"); system("pause"); return; }
    char newp[20]; printf("输入新密码: "); HidePassword(newp);
    char confirm[20]; printf("确认密码: "); HidePassword(confirm);
    if (strcmp(newp, confirm) != 0) { printf("两次密码不一致。\n"); system("pause"); return; }
    strncpy(users[idx].password, newp, sizeof(users[idx].password) - 1);
    printf("密码已重置。\n"); system("pause");
}

// stats & returns implemented in manager file for admin
void stat_top5() {
    typedef struct { int pid; int qty; } Agg;
    Agg aggs[MAX_PRODUCTS];
    int an = 0;
    for (int i = 0; i < saleCount; i++) {
        int pid = sales[i].productId; int found = -1;
        for (int j = 0; j < an; j++) if (aggs[j].pid == pid) { found = j; break; }
        if (found == -1) { aggs[an].pid = pid; aggs[an].qty = sales[i].quantity; an++; }
        else aggs[found].qty += sales[i].quantity;
    }
    for (int i = 0; i < an; i++) for (int j = i + 1; j < an; j++) if (aggs[j].qty > aggs[i].qty) { Agg t = aggs[i]; aggs[i] = aggs[j]; aggs[j] = t; }
    printf("=== Top5 销量商品 ===\n");
    for (int i = 0; i < an && i < 5; i++) printf("%d) ProductID:%d 销量:%d\n", i + 1, aggs[i].pid, aggs[i].qty);
    system("pause");
}

void stat_monthly() {
    typedef struct { char key[8]; int qty; } M;
    M ma[200]; int mn = 0;
    for (int i = 0; i < saleCount; i++) {
        if (strlen(sales[i].date) < 7) continue;
        char key[8] = { 0 }; strncpy(key, sales[i].date, 7);
        int f = -1; for (int j = 0; j < mn; j++) if (strcmp(ma[j].key, key) == 0) { f = j; break; }
        if (f == -1) { strcpy(ma[mn].key, key); ma[mn].qty = sales[i].quantity; mn++; }
        else ma[f].qty += sales[i].quantity;
    }
    printf("=== 月度销量 ===\n"); for (int i = 0; i < mn; i++) printf("%s : %d\n", ma[i].key, ma[i].qty);
    system("pause");
}

void check_stock_warning() {
    int th; printf("输入库存预警阈值: "); if (scanf("%d", &th) != 1) { printf("输入错误。\n"); system("pause"); return; }
    printf("=== 低于 %d 的商品 ===\n", th);
    for (int i = 0; i < productCount; i++) if (products[i].stock <= th) printf("ID:%s 名称:%s 库存:%d\n", products[i].id, products[i].name, products[i].stock);
    system("pause");
}

void return_product() {
    int saleId; printf("输入要退货的 SaleID: "); if (scanf("%d", &saleId) != 1) return;
    int sidx = -1; for (int i = 0; i < saleCount; i++) if (sales[i].saleId == saleId) { sidx = i; break; }
    if (sidx == -1) { printf("未找到销售记录。\n"); system("pause"); return; }
    Sale* s = &sales[sidx];
    printf("销售: ProductID:%d Qty:%d\n", s->productId, s->quantity);
    printf("输入退货数量(<=原数量): "); int q; if (scanf("%d", &q) != 1 || q <= 0 || q > s->quantity) { printf("数量错误。\n"); system("pause"); return; }
    Return r; r.returnId = nextReturnId++; r.saleId = s->saleId; r.productId = s->productId; r.quantity = q; time_t t = time(NULL); strftime(r.date, sizeof(r.date), "%Y-%m-%d %H:%M:%S", localtime(&t));
    if (returnCount < MAX_RETURNS) returnsArr[returnCount++] = r;
    char pidstr[16]; snprintf(pidstr, sizeof(pidstr), "%d", r.productId);
    int pidx = findProductIndexById(pidstr); if (pidx != -1) products[pidx].stock += q;
    printf("退货已记录(ReturnID=%d)。库存已返还。\n", r.returnId);
    system("pause");
}

void return_query() {
    printf("=== 退货记录(%d) ===\n", returnCount);
    for (int i = 0; i < returnCount; i++) printf("ReturnID:%d SaleID:%d PID:%d Qty:%d Time:%s\n", returnsArr[i].returnId, returnsArr[i].saleId, returnsArr[i].productId, returnsArr[i].quantity, returnsArr[i].date);
    system("pause");
}
