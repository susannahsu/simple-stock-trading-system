#include "orderUtils.h"
#include <random>
#include <iostream>
#include <fstream>
#include <cmath> // For std::abs

void generateAndWriteOrders(const std::vector<Portfolio>& portfolios, const std::vector<Stock>& stocks, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }
    
    std::default_random_engine generator(205); // For reproducibility
    std::normal_distribution<double> priceAdjustment(0.0, 0.3);

    for (const auto& portfolio : portfolios) {
        for (const auto& stock : stocks) {
            double basePrice = stock.getPrice();
            double volatility = stock.getVolatility();
            double riskTolerance = portfolio.getRiskTolerance();
            int availableShares = portfolio.getShares(stock.getStockId());
            
            if (availableShares == 0) continue; // Skip if no shares to sell
            
            // Calculate offer price
            double offerPrice = basePrice * (1 + priceAdjustment(generator) * (1 + riskTolerance * volatility));
            
            // Determine quantity
            int quantity = std::round(availableShares * riskTolerance * (1 - volatility));
            if (quantity == 0) continue; // Ensure the quantity is not zero
            
            // Random decision to buy or sell, but not both
            bool isBuyOrder = std::uniform_int_distribution<int>(0, 1)(generator);
            if (isBuyOrder) {
                outFile << portfolio.getTraderId() << "," << stock.getStockId() << "," << offerPrice << "," << -std::abs(quantity) << "\n"; // Buy
            } else {
                outFile << portfolio.getTraderId() << "," << stock.getStockId() << "," << offerPrice << "," << std::abs(quantity) << "\n"; // Sell
            }
        }
    }

    outFile.close();
}
