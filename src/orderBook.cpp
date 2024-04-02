#include "orderBook.h"
#include "order.h"
#include "portfolio.h"

#include <iostream>
#include <fstream>
#include <sstream>

OrderBook::OrderBook(){}

//
// File format, each line:
// int       int      double      int
// trader_id stock_id offer_price quantity

bool OrderBook::ReadOrdersFromFile(std::string fname) {
    std::ifstream f(fname);
    std::cout << "Reading order from file: " << fname << std::endl << std::endl;
    if (!f.is_open()) {
        std::cerr << "Failed to open " << fname << " for reading.\n" << std::endl;
        return false;
    }

    std::string line;

    // Skip headers
    // std::getline(f, line);

    while (std::getline(f, line)) {
        std::stringstream ss(line);
        int trader_id, stock_id, quantity;
        double offer_price;
        char comma; // To consume the commas

        if (ss >> trader_id >> comma >> stock_id >> comma >> offer_price >> comma >> quantity) {
            std::cout << "Read Order - Trader ID: " << trader_id << ", Stock ID: " << stock_id
                      << ", Offer Price: " << offer_price << ", Quantity: " << quantity << std::endl;
            orders.push_back(std::unique_ptr<Order>(new Order(trader_id, stock_id, offer_price, quantity)));
        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
            // Handle parsing error or skip line
        }
    }
    return true;
}

bool OrderBook::WriteRemainingOrdersToFile(std::string fname) {
    std::ofstream f(fname);
    if (!f.is_open()) {
        std::cerr << "Failed to open " << fname << " for writing.\n" << std::endl << std::endl;
        return false;
    }

    for (const auto& order : remainingOrders) {
        f << order->getTraderId() << ","
          << order->getStockId() << ","
          << order->getOfferPrice() << ","
          << order->getQuantity() << "\n";
    }

    return true;
}


void OrderBook::matchOrders() {
    std::cout << "=============================================================================" << std::endl;
    std::cout << "Starting to match orders. Total orders: " << orders.size() << std::endl << std::endl;
    std::map<int,std::vector<Order*>> buyOrders;
    std::map<int,std::vector<Order*>> sellOrders;
    std::map<int,std::vector<Order*>>::iterator it; // stock_id, order

    // sorting orders into buy and sell based on their stock_id
    for(int i=0; i<orders.size(); i++) {
        Order* currentOrder = orders[i].get();
        if (currentOrder->getQuantity() < 0) { // BUY
            std::cout << "Categorized as Buy: Stock ID " << currentOrder->getStockId() 
                      << ", Quantity " << currentOrder->getQuantity() << std::endl;
            it = buyOrders.find(currentOrder->getStockId());
            if(it != buyOrders.end()) {
                it->second.push_back(currentOrder);
            } else {
                std::vector<Order*> temp = {currentOrder};
                buyOrders[currentOrder->getStockId()] = temp;
            }
        } else if (currentOrder->getQuantity() > 0) { // SELL
            std::cout << "Categorized as Sell: Stock ID " << currentOrder->getStockId() 
                      << ", Quantity " << currentOrder->getQuantity() << std::endl;
            it = sellOrders.find(currentOrder->getStockId());
            if(it != sellOrders.end()) {
                it->second.push_back(currentOrder);
            } else {
                std::vector<Order*> temp = {currentOrder};
                sellOrders[currentOrder->getStockId()] = temp;
            }
        }
    }

    int totalBuyOrders = 0, totalSellOrders = 0;
    for (const auto& pair : buyOrders) {
        totalBuyOrders += pair.second.size();
    }
    for (const auto& pair : sellOrders) {
        totalSellOrders += pair.second.size();
    }

    std::cout << "Categorized " << totalBuyOrders << " buy orders and "
            << totalSellOrders << " sell orders for matching." << std::endl << std::endl;

    
    // the goal is to sort buyOrders & sellOrders into matchedOrders
    // and the unmatched once remain in buyOrders & sellOrders

    for(auto i = buyOrders.begin(); i != buyOrders.end(); i++){
        // go through stock id-s availble for buy
        it = sellOrders.find(i->first);// i->first == stock_id
        if(it == sellOrders.end()) {
            std::cout << "=============================================================================" << std::endl;
            std::cout << "No sell orders available for Stock ID " << i->first << std::endl << std::endl;
            continue; // no such stock_id availble
        } 

        // process orders
        std::vector<Order*> &ordersToBuy = i->second;
        std::vector<Order*> &ordersToSell = it->second;
        std::vector<std::pair<Order,Order>> matched;  // local vector for current stock_id matches

        // Debugging: Print number of orders to buy and sell for this stock ID
        std::cout << "=============================================================================" << std::endl;
        std::cout << "Matching for Stock ID " << i->first << ": " 
                  << ordersToBuy.size() << " buy orders, " 
                  << ordersToSell.size() << " sell orders." 
                  << std::endl << std::endl;

        for(int b=0; b<ordersToBuy.size(); b++){
            for(int s=0; s<ordersToSell.size(); s++){

                // Debug before matching attempt
                std::cout << "Attempting to match: Buy Order " << ordersToBuy[b]->getQuantity() << " @ " << ordersToBuy[b]->getOfferPrice()
                          << " with Sell Order " << ordersToSell[s]->getQuantity() << " @ " << ordersToSell[s]->getOfferPrice() << std::endl;

                if(ordersToSell[s]->getQuantity() == 0 || ordersToSell[s]->getOfferPrice() > ordersToBuy[b]->getOfferPrice()) {
                    std::cout << "No match due to quantity or price conditions." << std::endl << std::endl;
                    continue;
                }

                // logic for matching orders
                int quantityToBuy = std::abs(ordersToBuy[b]->getQuantity());
                int quantityToSell = ordersToSell[s]->getQuantity();

                std::cout << "Proceeding with match. Quantity to Buy: " << quantityToBuy 
                          << ", Quantity to Sell: " << quantityToSell << std::endl;

                if (quantityToBuy >= quantityToSell) {
                    // Adjust quantities based on the transaction
                    Order buy = *ordersToBuy[b];
                    Order sell = *ordersToSell[s];
                    

                    // int tradeQuantity = sell.getQuantity(); // actual quantity traded
                    // double tradePrice = std::min(buy.getOfferPrice(), sell.getOfferPrice());
                    // double cashExchanged = tradePrice * tradeQuantity;
                    // // For the buyer, subtract the cash spent
                    // portfolios[ordersToBuy[b]->getTraderId()]->adjustPnL(-cashExchanged);
                    // // For the seller, add the cash received
                    // portfolios[ordersToSell[s]->getTraderId()]->adjustPnL(cashExchanged);

                    buy.setQuantity(sell.getQuantity()); // Setting buy order quantity to sell quantity for matching
                    ordersToBuy[b]->setQuantity(ordersToBuy[b]->getQuantity() + sell.getQuantity());
                    ordersToSell[s]->setQuantity(0);
                    matched.push_back(std::make_pair(sell, buy)); // Copy data
                    std::cout << "Matched. New Buy Quantity: " << ordersToBuy[b]->getQuantity() 
                              << ", New Sell Quantity: " << ordersToSell[s]->getQuantity() << std::endl << std::endl;
                } else {
                    Order sell = *ordersToSell[s];
                    Order buy = *ordersToBuy[b];
                    sell.setQuantity(buy.getQuantity());
                    ordersToSell[s]->setQuantity(ordersToSell[s]->getQuantity() - quantityToBuy);
                    ordersToBuy[b]->setQuantity(0);
                    matched.push_back(std::make_pair(sell, buy)); // Copy data
                    std::cout << "Matched. New Buy Quantity: " << ordersToBuy[b]->getQuantity() 
                              << ", New Sell Quantity: " << ordersToSell[s]->getQuantity() << std::endl << std::endl;
                }
            } // for sell

            if(ordersToBuy[b]->getQuantity() == 0) break;
            std::cout << "Completed matching for Stock ID " << i->first << ". Matches made: " << matched.size() << std::endl << std::endl;

        }// for buy
        matchedOrders.emplace(i->first, matched);
        int totalMatchedOrders = 0; // Initialize counter for total matched orders

        // Iterate through all entries in matchedOrders to sum up the sizes of all matched vectors
        for (const auto& entry : matchedOrders) {
            const auto& matchesForStock = entry.second; // entry.second is the vector of matched orders for the stock
            totalMatchedOrders += matchesForStock.size(); // Add the number of matches for this stock to the total
        }

        std::cout << "=============================================================================" << std::endl;
        std::cout << "Total number of matched orders across all stock IDs: " << totalMatchedOrders << std::endl;
            
    }// i, stock_id

    for(auto b = buyOrders.begin(); b!=buyOrders.end(); b++){
        //std::vector<Order*> buy = b->second
        for(int i=0; i<b->second.size(); i++){
            if(b->second[i]->getQuantity()==0) continue;
            remainingOrders.push_back(b->second[i]);
        }
    }

    for(auto s = sellOrders.begin(); s!=sellOrders.end(); s++){
        //std::vector<Order*> sell = s->second
        for(int i=0; i<s->second.size(); i++){
            if(s->second[i]->getQuantity()==0) continue;
            remainingOrders.push_back(s->second[i]);
        }
    }

    std::cout << "=============================================================================" << std::endl;
    std::cout << "Final review of unmatched orders:" << std::endl;
    for(const auto& order : remainingOrders) {
        std::cout << "Unmatched Order - Trader ID: " << order->getTraderId()
                << ", Stock ID: " << order->getStockId()
                << ", Quantity: " << order->getQuantity()
                << ", Offer Price: " << order->getOfferPrice() << std::endl;
    }
    std::cout << "=============================================================================" << std::endl;
    std::cout << "Total Remaining Unmatched Orders: " << remainingOrders.size() << std::endl << std::endl;

}

