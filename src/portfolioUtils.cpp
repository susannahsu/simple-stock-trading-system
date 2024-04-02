#include "portfolioUtils.h"
#include <random>
#include <iostream>
#include <algorithm>

void distributeSharesRandomly(std::vector<Portfolio>& portfolios, const std::vector<Stock>& stocks) {
    std::default_random_engine generator(205); // Seed for reproducibility
    
    for (const auto& stock : stocks) {
        std::vector<int> traderIndices(portfolios.size());
        std::iota(traderIndices.begin(), traderIndices.end(), 0); // Fill with indices 0, 1, ..., portfolios.size() - 1

        int sharesRemaining = 100;
        while (sharesRemaining > 0) {
            std::shuffle(traderIndices.begin(), traderIndices.end(), generator); // Randomly shuffle trader indices
            for (int idx : traderIndices) {
                if (sharesRemaining <= 0) break;

                int maxSharesForTrader = std::min(sharesRemaining, 30); // Limit max shares per trader per round to prevent hoarding
                std::uniform_int_distribution<int> dist(1, maxSharesForTrader); // Distribute between 1 and maxSharesForTrader shares
                int sharesToAssign = dist(generator);

                portfolios[idx].assignShares(stock.getStockId(), sharesToAssign);
                sharesRemaining -= sharesToAssign;
            }
        }
    }
}
