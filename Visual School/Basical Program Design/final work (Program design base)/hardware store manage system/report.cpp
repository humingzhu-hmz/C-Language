#include "framework.h"

ProductReport query_product_report(const char* productId) {
    ProductReport r; memset(&r, 0, sizeof(r));
    int pidx = -1;
    for (int i = 0; i < productCount; i++) if (strcmp(products[i].id, productId) == 0) { pidx = i; break; }
    if (pidx == -1) return r;
    r.product = products[pidx];
    r.currentStock = products[pidx].stock;
    int pid = atoi(productId);
    int sc = 0, rc = 0, stc = 0;
    for (int i = 0; i < saleCount; i++) if (sales[i].productId == pid) sc++;
    for (int i = 0; i < returnCount; i++) if (returnsArr[i].productId == pid) rc++;
    for (int i = 0; i < stockRecordCount; i++) if (stockRecords[i].productId == pid) stc++;
    if (sc > 0) {
        r.sales = (Sale*)malloc(sizeof(Sale) * sc); int k = 0;
        for (int i = 0; i < saleCount; i++) if (sales[i].productId == pid) { r.sales[k++] = sales[i]; r.totalSold += sales[i].quantity; }
        r.saleCount = sc;
    }
    else { r.sales = NULL; r.saleCount = 0; }
    if (rc > 0) {
        r.returns = (Return*)malloc(sizeof(Return) * rc); int k = 0;
        for (int i = 0; i < returnCount; i++) if (returnsArr[i].productId == pid) { r.returns[k++] = returnsArr[i]; r.totalReturned += returnsArr[i].quantity; }
        r.returnCount = rc;
    }
    else { r.returns = NULL; r.returnCount = 0; }
    if (stc > 0) {
        r.stockHistory = (StockRecord*)malloc(sizeof(StockRecord) * stc); int k = 0;
        for (int i = 0; i < stockRecordCount; i++) if (stockRecords[i].productId == pid) { r.stockHistory[k++] = stockRecords[i]; r.totalAddedStock += stockRecords[i].quantityAdded; }
        r.stockHistoryCount = stc;
    }
    else { r.stockHistory = NULL; r.stockHistoryCount = 0; }
    r.isNewlyAdded = (r.stockHistoryCount == 1);
    r.isOutOfStock = (r.currentStock <= 0);
    return r;
}

void free_product_report(ProductReport* r) {
    if (!r) return;
    if (r->sales) { free(r->sales); r->sales = NULL; }
    if (r->returns) { free(r->returns); r->returns = NULL; }
    if (r->stockHistory) { free(r->stockHistory); r->stockHistory = NULL; }
    r->saleCount = r->returnCount = r->stockHistoryCount = 0;
}
