# Market Microstructure Simulator

## Overview

This project implements a simplified electronic exchange in C++.

The simulator maintains buy and sell order books, performs order matching based on price-time priority, executes trades, supports partial fills, and calculates basic market statistics such as bid-ask spread.

## Features

* Buy and Sell Order Books
* Price-Time Priority Matching
* Partial Order Fills
* Bid-Ask Spread Calculation
* Trade Execution Tracking
* Order Book Sorting

## Technologies Used

* C++
* STL Vector
* STL Algorithms
* Object-Oriented Programming

## Matching Logic

Orders are matched according to the following rules:

1. Higher buy prices receive priority.
2. Lower sell prices receive priority.
3. If prices are equal, earlier timestamps receive priority.

This follows the price-time priority mechanism used in many electronic exchanges.

## Example

BUY Order:

Price: 100

Quantity: 50

SELL Order:

Price: 99

Quantity: 30

Result:

Trade Executed: 30 shares

Remaining Buy Quantity: 20

Remaining Sell Quantity: 0

## Future Improvements

* Priority Queue Based Order Books
* Market Orders
* Order Cancellation
* Performance Benchmarking
* Real-Time Order Book Visualization

## Author

B.Tech Electrical Engineering, IIT Kharagpur
