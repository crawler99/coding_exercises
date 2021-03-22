#ifndef _VIVCOURT_ORDER_BOOK_H_
#define _VIVCOURT_ORDER_BOOK_H_

#include <unordered_map>

template <typename BookTraits>
class OrderBook
{
public:
    std::size_t GetBookSize();

private:
    std::unordered_map<BookTraits::PriceType, int> _book;
};

#endif // _VIVCOURT_ORDER_BOOK_H_
