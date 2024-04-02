#ifndef PORTFOLIO_UTILS_H
#define PORTFOLIO_UTILS_H

#include <vector>
#include "portfolio.h"
#include "stock.h"

void distributeSharesRandomly(std::vector<Portfolio>& portfolios, const std::vector<Stock>& stocks);

#endif // PORTFOLIO_UTILS_H
