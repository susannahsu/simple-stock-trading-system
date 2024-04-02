#ifndef STOCK_H
#define STOCK_H

class Stock {
private:
    int stock_id;
    double price;
    double vol_rating;

public:
    Stock(int id, double price, double vol_rating);

    int getStockId() const;
    double getPrice() const;
    void updatePrice(double newPrice);
    double getVolatility() const;
};

#endif // STOCK_H
