=============
Build and Run
=============

> cd build/
> cmake ..
> make
> make test
> make install

It requires C++17 support from compiler and a cmake version >= 3.1.

The built application is named order_book and will be installed under {pkg_root}/bin/. If no argument is provided to run, it shows the command-line usage.

To extract top-5 price depth, run:

> ./order_book 5 input1.stream

To extract full price depth, run:

> ./order_book full input1.stream

=============
Design Notes
=============
- Assume the processing on OrderBook is done by single thread.
- Assume the order volume in "Order Added" or "Order Updated" message is non-zero.
- For simplicity, use std::map to store the full price depth of a side. To improve performance, we can either use a vector/array to store the full price depth, or use a vector/array to store the top N price levels and leave the rest levels to a std::map. This highly depends on how many price levels we need to report and the market data character.
- For simplicity, only print error messages for invalid command line arguments. There should be detailed guidelines of how errors must be handled for a production system.
- For simplicity, always read the entire input from a disk file before starting to consume.
- The depth is reported to standard output using STL ostream. This is slow from performance perspective but is not a concern for this homework.
