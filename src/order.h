#ifndef ORDER_H
#define ORDER_H

class Order {
private:
    int trader_id;
    int stock_id;
    double offer_price; // Adjusted offer price, not the base price
    int quantity; // Negative for buy orders, positive for sell orders

public:
    // Constructor to initialize an order
    Order(int traderId, int stockId, double offerPrice, int quantity);

    // Getters
    int getTraderId() const;
    int getStockId() const;
    double getOfferPrice() const;
    int getQuantity() const;

    // Setter for quantity
    void setQuantity(int newQuantity);


};

#endif // ORDER_H
