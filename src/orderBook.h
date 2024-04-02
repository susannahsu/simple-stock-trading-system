#include "order.h"

#include <vector>
#include <map>
#include <string>

class OrderBook {
public:
        OrderBook();
        bool ReadOrdersFromFile(std::string fname);        
        bool WriteRemainingOrdersToFile(std::string fname);        
        void matchOrders();
private:
        std::vector<std::unique_ptr<Order>> orders;
        std::map<int,std::vector<std::pair<Order,Order>>> matchedOrders;
        std::vector<Order*> remainingOrders;
};
