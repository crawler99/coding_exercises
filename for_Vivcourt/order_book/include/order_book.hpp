#ifndef _VIVCOURT_ORDER_BOOK_H_
#define _VIVCOURT_ORDER_BOOK_H_

#include <map>
#include <unordered_map>
#include <optional>

namespace vivcourt
{
    template <typename BookTraits>
    class PriceLevel
    {
    public:
        void AddOrder(const BookTraits::OrderId orderId, const BookTraits::OrderVolume orderVolume)
        {
            _total_volume += orderVolume;
            _order_volumes[orderId] += orderVolume;
        }

    private:
        BookTraits::OrderVolume _total_volume{};
        std::unordered_map<BookTraits::OrderId, BookTraits::OrderVolume> _order_volumes;
    };

    template <typename BookTraits>
    class Side
    {
    public:
        std::optional<PriceLevel<BookTraits>&> GetPriceLevel(const BookTraits::OrderPrice &price)
        {
            auto it = _priceLevels.find(price);
            if (it != _priceLevels.end())
            {
                return it->second;
            }
            return std::nullopt;
        }

    private:
        std::map<BookTraits::OrderPrice, PriceLevel<BookTraits>> _priceLevels;
    };

    template <typename BookTraits>
    class OrderBook
    {
    public:
        std::size_t GetBookSize();

    private:
        std::unordered_map<BookTraits::PriceType, int> _book;
    };

}

#endif // _VIVCOURT_ORDER_BOOK_H_
