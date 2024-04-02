#include <fstream>
#include <random>
#include <iostream>
#include "portfolio.h"
#include "stock.h"
#include "order.h"

// Constructor implementation
Order::Order(int traderId, int stockId, double offerPrice, int quantity)
    : trader_id(traderId), stock_id(stockId), offer_price(offerPrice), quantity(quantity) {}

// Getter for trader_id
int Order::getTraderId() const {
    return trader_id;
}

// Getter for stock_id
int Order::getStockId() const {
    return stock_id;
}

// Getter for offer_price
double Order::getOfferPrice() const {
    return offer_price;
}

// Getter for quantity
int Order::getQuantity() const {
    return quantity;
}

void Order::setQuantity(int newQuantity) {
    quantity = newQuantity;
}


