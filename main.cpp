#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

/*
    Represents a single order submitted to the exchange.

    id         : Unique order identifier
    isBuy      : true = Buy Order, false = Sell Order
    price      : Limit price of the order
    quantity   : Number of shares/contracts
    timestamp  : Arrival time used for time priority
*/
struct Order
{
    int id;
    bool isBuy;
    double price;
    int quantity;
    int timestamp;
};

/*
    Buy-side comparator.

    Priority Rules:
    1. Higher price gets higher priority.
    2. If prices are equal, earlier timestamp wins.

    This implements price-time priority.
*/
struct BuyComparator
{
    bool operator()(const Order &a, const Order &b) const
    {
        if (a.price != b.price)
            return a.price < b.price;

        return a.timestamp > b.timestamp;
    }
};

/*
    Sell-side comparator.

    Priority Rules:
    1. Lower price gets higher priority.
    2. If prices are equal, earlier timestamp wins.

    This mirrors the behavior of a real exchange.
*/
struct SellComparator
{
    bool operator()(const Order &a, const Order &b) const
    {
        if (a.price != b.price)
            return a.price > b.price;

        return a.timestamp > b.timestamp;
    }
};

/*
    Matching Engine

    Responsibilities:
    - Maintain buy and sell order books
    - Accept incoming orders
    - Match compatible orders
    - Track statistics
*/
class MatchingEngine
{
private:

    // Buy orders stored in a max-priority queue
    priority_queue<
        Order,
        vector<Order>,
        BuyComparator> buyBook;

    // Sell orders stored in a min-priority queue
    priority_queue<
        Order,
        vector<Order>,
        SellComparator> sellBook;

    int tradesExecuted = 0;
    int ordersProcessed = 0;

public:

    /*
        Adds a new order to the exchange.

        Orders are inserted into the appropriate
        order book and matching is attempted immediately.
    */
    void addOrder(Order order)
    {
        ordersProcessed++;

        if (order.isBuy)
            buyBook.push(order);
        else
            sellBook.push(order);

        match();
    }

    /*
        Core matching algorithm.

        While:
        Best Bid >= Best Ask

        execute trades.

        Supports:
        - Price-Time Priority
        - Partial Fills
    */
    void match()
    {
        while (!buyBook.empty() &&
               !sellBook.empty() &&
               buyBook.top().price >= sellBook.top().price)
        {
            Order buy = buyBook.top();
            buyBook.pop();

            Order sell = sellBook.top();
            sellBook.pop();

            int tradedQty =
                min(buy.quantity, sell.quantity);

            cout << "\n================================";
            cout << "\nTRADE EXECUTED";
            cout << "\n================================\n";

            cout << "Buy Order ID : "
                 << buy.id
                 << endl;

            cout << "Sell Order ID: "
                 << sell.id
                 << endl;

            cout << "Trade Price  : "
                 << sell.price
                 << endl;

            cout << "Trade Qty    : "
                 << tradedQty
                 << endl;

            // Reduce remaining quantities
            buy.quantity -= tradedQty;
            sell.quantity -= tradedQty;

            tradesExecuted++;

            /*
                If an order is only partially filled,
                reinsert the remaining quantity back
                into the order book.
            */
            if (buy.quantity > 0)
                buyBook.push(buy);

            if (sell.quantity > 0)
                sellBook.push(sell);
        }
    }

    /*
        Displays current market information.

        Best Bid = Highest Buy Price
        Best Ask = Lowest Sell Price
        Spread   = Ask - Bid
    */
    void printMarketData()
    {
        cout << "\n================================";
        cout << "\nMARKET DATA";
        cout << "\n================================\n";

        if (!buyBook.empty())
        {
            cout << "Best Bid: "
                 << buyBook.top().price
                 << endl;
        }

        if (!sellBook.empty())
        {
            cout << "Best Ask: "
                 << sellBook.top().price
                 << endl;
        }

        if (!buyBook.empty() &&
            !sellBook.empty())
        {
            cout << "Spread: "
                 << sellBook.top().price -
                        buyBook.top().price
                 << endl;
        }
    }

    /*
        Displays simulation statistics.
    */
    void printStatistics()
    {
        cout << "\n================================";
        cout << "\nSTATISTICS";
        cout << "\n================================\n";

        cout << "Orders Processed: "
             << ordersProcessed
             << endl;

        cout << "Trades Executed : "
             << tradesExecuted
             << endl;

        cout << "Open Buy Orders : "
             << buyBook.size()
             << endl;

        cout << "Open Sell Orders: "
             << sellBook.size()
             << endl;
    }
};

int main()
{
    MatchingEngine engine;

    /*
        Random order generation.

        This simulates multiple market participants
        submitting orders to the exchange.
    */
    mt19937 rng(time(0));

    uniform_int_distribution<int> sideDist(0, 1);
    uniform_int_distribution<int> priceDist(95, 105);
    uniform_int_distribution<int> qtyDist(10, 100);

    int timestamp = 1;

    /*
        Generate 100 random orders.
    */
    const int NUM_ORDERS = 100;
    
    for (int i = 1; i <= NUM_ORDERS; i++)
    {
        Order order;

        order.id = i;
        order.isBuy = sideDist(rng);
        order.price = priceDist(rng);
        order.quantity = qtyDist(rng);
        order.timestamp = timestamp++;

        engine.addOrder(order);
    }

    engine.printMarketData();
    engine.printStatistics();

    return 0;
}
