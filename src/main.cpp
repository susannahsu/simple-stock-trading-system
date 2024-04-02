// #include "orderBook.h" 

// #include <iostream>

// int main() {
    
//     OrderBook book;
//     if(!book.ReadOrdersFromFile("orders_in.dat")){
//         std::cout << "can't read\n";
//     }        
//     book.matchOrders();
//     if(!book.WriteRemainingOrdersToFile("orders_out.dat")){        
//         std::cout << "can't write\n";
//     }        
    
//     return 0;
// }


#include <iostream>
#include "dataLoader.h"
#include "portfolio.h"
#include "portfolioUtils.h"
#include "order.h"
#include "orderUtils.h"
#include "orderBook.h" 

int main() {
    // Load traders and stocks
    auto traders = readTradersFromFile("../data/traders.csv");
    auto stocks = readStocksFromFile("../data/stocks.csv");

    // Print loaded traders
    std::cout << "Traders loaded:" << std::endl;
    for (const auto& trader : traders) {
        std::cout << "Trader ID: " << trader.getTraderId()
                  << ", PNL: " << trader.getPnl()
                  << ", Risk Tolerance: " << trader.getRiskTolerance()
                  << std::endl;
    }
    std::cout << "=============================================================================" << std::endl;

    // Print loaded stocks
    std::cout << "\nStocks loaded:" << std::endl;
    for (const auto& stock : stocks) {
        std::cout << "Stock ID: " << stock.getStockId()
                  << ", Price: " << stock.getPrice()
                  << ", Volatility: " << stock.getVolatility()
                  << std::endl;
    }
    std::cout << "=============================================================================" << std::endl;

    std::vector<Portfolio> portfolios;
    for (const auto& trader : traders) {
        portfolios.emplace_back(trader.getTraderId(), trader.getPnl(), trader.getRiskTolerance());
    }
    
    distributeSharesRandomly(portfolios, stocks);

    // For debugging: Print portfolios to verify distribution
    for (const auto& portfolio : portfolios) {
        portfolio.printPortfolio();
    }
    std::cout << "=============================================================================" << std::endl;

    // Calculate and print the sum of shares for each stock
    std::cout << "\nSum of shares for each stock:" << std::endl;
    for (const auto& stock : stocks) {
        int totalShares = 0;
        for (const auto& portfolio : portfolios) {
            // if (portfolio.stockHoldings.find(stock.getStockId()) != portfolio.stockHoldings.end()) {
            //     totalShares += portfolio.stockHoldings.at(stock.getStockId());
            // }
            int shares = portfolio.getShares(stock.getStockId());
            if (shares > 0) {
                totalShares += shares;
            }
        }
        std::cout << "Stock ID: " << stock.getStockId() << ", Total Shares: " << totalShares << std::endl;
        std::cout << "=============================================================================" << std::endl;
    }

    generateAndWriteOrders(portfolios, stocks, "order.csv");

    OrderBook book;
    if(!book.ReadOrdersFromFile("../tests/test_orders_5.csv")){
        std::cout << "can't read\n";
    }        
    book.matchOrders();
    if(!book.WriteRemainingOrdersToFile("../tests/test_orders_5_out.csv")){        
        std::cout << "can't write\n";
    }        

    return 0;
}
