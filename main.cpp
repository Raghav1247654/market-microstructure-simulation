#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Order
{
public:
    int id;
    bool isBuy;
    double price;
    int quantity;
    int timestamp;
};

void printOrder(Order order)
{
    cout << "ID: " << order.id
         << " | Price: " << order.price
         << " | Qty: " << order.quantity
         << " | Time: " << order.timestamp
         << endl;
}

int tradesExecuted = 0;

void matchOrders(Order &buy, Order &sell)
{
    if (buy.quantity == 0 || sell.quantity == 0)
    {
        return;
    }

    if (buy.price >= sell.price)
    {
        int tradedQuantity =
            min(buy.quantity, sell.quantity);

        cout << "\n====================\n";
        cout << "TRADE EXECUTED\n";
        cout << "Buy Order ID : " << buy.id << endl;
        cout << "Sell Order ID: " << sell.id << endl;
        cout << "Trade Price  : " << sell.price << endl;
        cout << "Trade Qty    : " << tradedQuantity << endl;

        buy.quantity -= tradedQuantity;
        sell.quantity -= tradedQuantity;

        tradesExecuted++;
    }
}

int main()
{
    vector<Order> buyBook;
    vector<Order> sellBook;

    // BUY ORDERS

    Order buy1;
    buy1.id = 1;
    buy1.isBuy = true;
    buy1.price = 100;
    buy1.quantity = 50;
    buy1.timestamp = 2;

    Order buy2;
    buy2.id = 2;
    buy2.isBuy = true;
    buy2.price = 101;
    buy2.quantity = 20;
    buy2.timestamp = 3;

    Order buy3;
    buy3.id = 3;
    buy3.isBuy = true;
    buy3.price = 100;
    buy3.quantity = 40;
    buy3.timestamp = 1;

    buyBook.push_back(buy1);
    buyBook.push_back(buy2);
    buyBook.push_back(buy3);

    // SELL ORDERS

    Order sell1;
    sell1.id = 4;
    sell1.isBuy = false;
    sell1.price = 98;
    sell1.quantity = 10;
    sell1.timestamp = 1;

    Order sell2;
    sell2.id = 5;
    sell2.isBuy = false;
    sell2.price = 100;
    sell2.quantity = 25;
    sell2.timestamp = 2;

    Order sell3;
    sell3.id = 6;
    sell3.isBuy = false;
    sell3.price = 102;
    sell3.quantity = 30;
    sell3.timestamp = 3;

    sellBook.push_back(sell1);
    sellBook.push_back(sell2);
    sellBook.push_back(sell3);

    cout << "INITIAL BUY BOOK\n\n";

    for (Order order : buyBook)
    {
        printOrder(order);
    }

    cout << "\nINITIAL SELL BOOK\n\n";

    for (Order order : sellBook)
    {
        printOrder(order);
    }

    // PRICE-TIME PRIORITY

    sort(buyBook.begin(), buyBook.end(),
         [](Order a, Order b)
         {
             if (a.price != b.price)
             {
                 return a.price > b.price;
             }

             return a.timestamp < b.timestamp;
         });

    sort(sellBook.begin(), sellBook.end(),
         [](Order a, Order b)
         {
             if (a.price != b.price)
             {
                 return a.price < b.price;
             }

             return a.timestamp < b.timestamp;
         });

    cout << "\n================================\n";
    cout << "PRICE-TIME PRIORITY ORDER BOOKS";
    cout << "\n================================\n";

    cout << "\nBUY BOOK\n\n";

    for (Order order : buyBook)
    {
        printOrder(order);
    }

    cout << "\nSELL BOOK\n\n";

    for (Order order : sellBook)
    {
        printOrder(order);
    }

    double bestBid = buyBook[0].price;
    double bestAsk = sellBook[0].price;

    cout << "\n================================\n";
    cout << "MARKET DATA";
    cout << "\n================================\n";

    cout << "Best Bid: " << bestBid << endl;
    cout << "Best Ask: " << bestAsk << endl;
    cout << "Spread  : " << bestAsk - bestBid << endl;

    cout << "\n================================\n";
    cout << "MATCHING ENGINE";
    cout << "\n================================\n";

    for (Order &buy : buyBook)
    {
        for (Order &sell : sellBook)
        {
            matchOrders(buy, sell);
        }
    }

    cout << "\n================================\n";
    cout << "FINAL BUY BOOK";
    cout << "\n================================\n";

    for (Order order : buyBook)
    {
        printOrder(order);
    }

    cout << "\n================================\n";
    cout << "FINAL SELL BOOK";
    cout << "\n================================\n";

    for (Order order : sellBook)
    {
        printOrder(order);
    }

    cout << "\n================================\n";
    cout << "STATISTICS";
    cout << "\n================================\n";

    cout << "Trades Executed: "
         << tradesExecuted
         << endl;

    return 0;
}