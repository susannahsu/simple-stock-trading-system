# Serial Baseline Simple Stock Trading System

## Serial Baseline

### Classes

`Stock`
* Represents a stock with an ID, price, and volatility rating.
* Constructor: Initializes a Stock with an ID, initial price, and volatility rating.
* Getters: Methods to retrieve the stock's ID, price, and volatility.
* `updatePrice(double newPrice)` (*have not use yet, for future need*): Updates the stock's price.

`Trader`
* Represents a trader with an ID, profit and loss (PnL, here we simplify to the amount of capital available), and risk tolerance (which will influence the offer price they are willing to buy or sell and the amount they are willing to trade).
* Constructor: Initializes a Trader with an ID, initial PnL, and risk tolerance.
* Getters and Setters: Methods to get and set the trader's ID, PnL, and risk tolerance.

`Order`
* Represents a trading order with details such as trader ID, stock ID, offer price, and quantity.
* Constructor: Initializes an Order with the provided details.
* Getters: Methods to retrieve order details.
* `setQuantity(int newQuantity)`: Updates the quantity of the order.

`Portfolio`
* Represents a trader's portfolio, including stock holdings and their associated quantities.
* Constructor: Initializes a Portfolio with an ID, PnL, and risk tolerance.
* Getters: Methods to get portfolio details and the number of shares of a specific stock.
* `assignShares(int stock_id, int shares)`: Assigns a specific number of shares of a stock to the portfolio.
* `adjustPnL(double amount)`: Adjusts the PnL of the portfolio.
* `printPortfolio() const`: Prints the portfolio details.

`OrderBook`
* Manages a collection of orders and facilitates the matching of buy and sell orders.
* Constructor: Initializes an OrderBook.
* `ReadOrdersFromFile(std::string fname)`: Reads orders from a file and populates the order book.
* `WriteRemainingOrdersToFile(std::string fname)`: Writes the unmatched orders to a file.
* `matchOrders()`: Matches buy and sell orders within the order book.

### Utility Functions
`distributeSharesRandomly`
* Located in `portfolioUtils.h/cpp`.
* Initialize the portfolio by distributing shares among portfolios randomly, considering the available stocks (here we assume that each stock has 100 shares available at the beginning).

`generateAndWriteOrders`
* Located in `orderUtils.h/cpp`.
* Generates trading orders based on the portfolios and stocks, then writes these orders to a file.

`readTradersFromFile` and `readStocksFromFile`
* Located in `dataLoader.h/cpp`.
* Functions for loading traders and stocks from CSV files.

### Overview
The system simulates a trading environment where traders, represented by Trader objects, can own stocks, represented by `Stock` objects, within their `Portfolio`. `Orders` can be created to buy or sell stocks, and an `OrderBook` manages these orders, attempting to match buy and sell orders based on their details.

Utility functions assist in initializing the simulation by loading data from files (`readTradersFromFile` and `readStocksFromFile`), distributing stocks among traders (`distributeSharesRandomly`), and generating orders based on the current state of the portfolios (`generateAndWriteOrders`).

### Files for Data Generation
* `generate_stocks.cpp`: Generates a list of stocks with random prices and volatility ratings, writing them to a CSV file.
* `generate_traders.cpp`: Generates a list of traders with random PnL and risk tolerance values, writing them to a CSV file.

### Assumptions and Simplifications
1. Fixed Number of Shares per Stock: The system assumes that each stock has a fixed number of shares (100 shares) available at the beginning of the simulation. This simplification ignores the possibility of additional shares being issued or shares being bought back by the company.
2. Random Distribution of Shares: Shares are distributed randomly among traders' portfolios at the start of the simulation. This method doesn't consider the traders' strategies, historical performance, or preferences.
3. Order Matching Timing: The simulation assumes that order matching occurs after all orders have been placed, similar to a batch processing system or an end-of-day matching system. This simplification ignores the continuous and dynamic nature of actual trading markets where orders can be matched in real-time.
4. Simplified Order Matching Logic: The order matching logic in `OrderBook` is simplified and may not fully capture the complexities of real-world order matching mechanisms, such as price-time priority, partial fills, and handling of orders across different market conditions.
5. Fixed Random Seed: The use of a fixed random seed (`205`) in generating stocks and traders ensures reproducibility of the data across runs.
6. Single Day Simulation: The system only simulates trading activities within a single day, without considering the impact of multi-day strategies, overnight risk, or changes in market conditions over longer periods.
7. No External Market Influences: The simulation does not account for external market influences or news events that could impact stock prices, trader decisions, or market dynamics.
8. Uniform Risk Tolerance and PnL Calculation: The system simplifies risk tolerance and PnL calculations, not accounting for more sophisticated risk management strategies or diverse portfolio performance metrics.
9. Static Stock Attributes: Stock prices and volatility ratings are generated once and remain static. This does not reflect the continuous fluctuation of stock prices and volatility in real markets.
10. Simplified Trader Behavior: Traders' decision-making processes are simplified, with buy or sell orders generated based on random distributions and predefined logic, rather than dynamic strategies or reactions to market conditions.


### Order Generation Logic
Encapsulated within the `generateAndWriteOrders` function, defined in `orderUtils.cpp`. This function generates orders based on the portfolios and stocks available, taking into account each trader's risk tolerance and the volatility of the stocks.
1. Initialization: The function starts by opening a file (specified by filename) where the generated orders will be written. It also initializes a random number generator with a fixed seed for reproducibility.
2. Iterate Through Portfolios: For each portfolio in the list of portfolios:
    - The portfolio's risk tolerance is considered.
    - Each stock available in the market is examined.
3. For Each Stock in a Portfolio:
    - The base price of the stock and its volatility are retrieved.
    - The available shares of the stock within the current portfolio are checked. If there are no shares available, the function moves to the next stock.
    - An offer price for the order is calculated by adjusting the base price of the stock with a random factor influenced by the stock's volatility and the trader's risk tolerance. This introduces variability in the orders, simulating a real-world scenario where traders place orders at different prices based on their strategies and market views.
4. Determine Order Quantity:
    - The quantity for the order is determined by considering the trader's risk tolerance, the stock's volatility, and the number of shares available in the portfolio. This step ensures that the order size reflects both the trader's willingness to take on risk and the stock's inherent risk.
5. Random Decision to Buy or Sell:
    - A random decision is made for each order, determining whether it will be a buy or sell order. This simplification simulates traders' varied motivations and strategies without delving into complex behavioral models.
6. Writing Orders to File:
    - For each generated order, the details (trader ID, stock ID, offer price, and quantity) are written to the output file. The quantity is adjusted to be **negative for buy orders** and **positive for sell orders** to differentiate between the two types.


### Possible Parallelization Ideas

#### OpenMP
Best suited for shared-memory architectures and can be used to parallelize loop computations and certain independent tasks within a single process. In our system, OpenMP could be effectively used in:
* Share Distribution: The `distributeSharesRandomly` function involves iterating over stocks and portfolios to distribute shares. Since each stock's share distribution is independent of others, this process can be parallelized.
* Order Generation: Generating orders in `generateAndWriteOrders` can be parallelized at the level of processing multiple portfolios or stocks concurrently, as each order generation is independent until it's written out.
* Portfolio Updating: When adjusting portfolios based on order matches, if adjustments are independent, OpenMP can be used to parallelize these updates.

### MPI
Effective for distributed-memory systems and can help scale our simulation across multiple nodes or processes. It is particularly useful for data parallelism and task parallelism in distributed environments.
* Data Distribution: Initially loading and distributing stocks and traders' information across multiple processes. MPI I/O could be leveraged for reading the input files (stocks and traders) and distributing this data among different MPI processes.
* Order Matching in `OrderBook`: The matching process can be distributed by partitioning the order book among multiple MPI processes, each responsible for a subset of stocks. This approach would require communication between processes to update order statuses and match orders across partitions.
* Parallel File Writing with MPI I/O: Writing out the remaining unmatched orders and matched orders to files can be parallelized using MPI I/O, allowing multiple processes to write to the same file concurrently.











