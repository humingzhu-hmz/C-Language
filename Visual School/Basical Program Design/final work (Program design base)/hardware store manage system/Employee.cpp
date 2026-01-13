#include "framework.h"

void sale_product() {
    char id[16]; int q;
    printf("输入销售商品ID: "); if (scanf("%15s", id) != 1) return;
    int idx = -1; for (int i = 0; i < productCount; i++) if (strcmp(products[i].id, id) == 0) { idx = i; break; }
    if (idx == -1) { printf("未找到商品。\n"); system("pause"); return; }
    Product* p = &products[idx];
    printf("商品:%s 当前库存:%d\n", p->name, p->stock);
    printf("输入销售数量: "); if (scanf("%d", &q) != 1 || q <= 0) { printf("数量错误。\n"); system("pause"); return; }
    if (q > p->stock) { printf("库存不足。\n"); system("pause"); return; }
    p->stock -= q;
    Sale s; s.saleId = nextSaleId++; s.productId = atoi(p->id); s.quantity = q; time_t t = time(NULL); strftime(s.date, sizeof(s.date), "%Y-%m-%d %H:%M:%S", localtime(&t));
    if (saleCount < MAX_SALES) sales[saleCount++] = s;
    printf("销售已记录 (SaleID=%d)\n", s.saleId); system("pause");
}

void check_sales() {
    printf("=== 销售记录(%d) ===\n", saleCount);
    for (int i = 0; i < saleCount; i++) printf("SaleID:%d PID:%d Qty:%d Time:%s\n", sales[i].saleId, sales[i].productId, sales[i].quantity, sales[i].date);
    system("pause");
}

// employees don't own query_product_report; call shared one in report.cpp
// helper stats are in manager
