#ifndef ORDERUTILS_H
#define ORDERUTILS_H

#include "portfolio.h"
#include "stock.h"
#include <vector>
#include <string>

void generateAndWriteOrders(const std::vector<Portfolio>& portfolios, const std::vector<Stock>& stocks, const std::string& filename);

#endif // ORDERUTILS_H
