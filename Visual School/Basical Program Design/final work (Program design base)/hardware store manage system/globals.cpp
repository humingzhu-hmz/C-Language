#include "framework.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

Sale sales[MAX_SALES];
int saleCount = 0;

Return returnsArr[MAX_RETURNS];
int returnCount = 0;

StockRecord stockRecords[MAX_STOCK_RECORDS];
int stockRecordCount = 0;

User users[MAX_USERS];
int userCount = 0;

bool ISRUNNING = true;
User currentUser = { 0 };
State currentState = STATE_LOGIN;

int nextSaleId = 1;
int nextReturnId = 1;
int nextStockRecordId = 1;
