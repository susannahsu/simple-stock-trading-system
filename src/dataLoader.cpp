#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "trader.h"
#include "stock.h"

std::vector<Trader> readTradersFromFile(const std::string& filename) {
    std::vector<Trader> traders;
    std::ifstream file(filename);
    std::string line;

    getline(file, line); // Skip the header line
    
    while (getline(file, line)) {
        std::stringstream linestream(line);
        int trader_id;
        double pnl, risk_tolerance;
        char delim; // Variable to consume the commas
        
        linestream >> trader_id >> delim >> pnl >> delim >> risk_tolerance;
        if (!linestream.fail()) {
            traders.push_back(Trader(trader_id, pnl, risk_tolerance));
        } else {
            std::cerr << "Failed to parse trader line: " << line << std::endl;
        }
    }
    
    return traders;
}

std::vector<Stock> readStocksFromFile(const std::string& filename) {
    std::vector<Stock> stocks;
    std::ifstream file(filename);
    std::string line;

    getline(file, line); // Skip the header line
    
    while (getline(file, line)) {
        std::stringstream linestream(line);
        int stock_id;
        double price, vol_rating;
        char delim; // Variable to consume the commas
        
        linestream >> stock_id >> delim >> price >> delim >> vol_rating;
        if (!linestream.fail()) {
            stocks.push_back(Stock(stock_id, price, vol_rating));
        } else {
            std::cerr << "Failed to parse stock line: " << line << std::endl;
        }
    }
    
    return stocks;
}
