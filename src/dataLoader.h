#ifndef DATALOADER_H
#define DATALOADER_H

#include "trader.h"
#include "stock.h"
#include <vector>

std::vector<Trader> readTradersFromFile(const std::string& filename);
std::vector<Stock> readStocksFromFile(const std::string& filename);

#endif // DATALOADER_H
