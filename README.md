# Market Microstructure Simulator

## Overview

This project implements a simplified electronic exchange in C++.

The system maintains buy and sell order books using heap-based data structures (`priority_queue`) and performs trade execution using a price-time priority matching algorithm.

The simulator processes randomly generated orders and tracks key market statistics including bid price, ask price, spread, and trade activity.

## Features

* Buy and Sell Order Books
* Price-Time Priority Matching
* Partial Order Fills
* Bid-Ask Spread Calculation
* Trade Execution Analytics
* Random Order Simulation
* Heap-Based Order Book Management

## System Design

Order Submission
↓
Matching Engine
↓
Buy Book / Sell Book
↓
Trade Execution
↓
Market Statistics

## Technologies Used

* C++
* STL Priority Queue
* STL Vector
* Object-Oriented Programming
* Custom Comparators

## Matching Logic

The exchange follows price-time priority:

1. Higher buy prices receive priority.
2. Lower sell prices receive priority.
3. If prices are equal, earlier timestamps receive priority.

## Example Trade

Buy Order:
Price = 100
Quantity = 50

Sell Order:
Price = 99
Quantity = 30

Trade Result:
30 shares executed

Remaining Buy Quantity = 20
Remaining Sell Quantity = 0

## Future Improvements

* Market Orders
* Order Cancellation
* Real-Time Visualization
* Latency Benchmarking
* Multi-Threaded Matching Engine

## Complexity Analysis

Order Insertion:
O(log n)

Best Bid / Ask Retrieval:
O(1)

Trade Matching:
O(log n) per heap operation

The use of priority queues enables efficient retrieval of the highest-priority buy order and lowest-priority sell order.

