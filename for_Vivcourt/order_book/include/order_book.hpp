#ifndef _VIVCOURT_ORDER_BOOK_H_
#define _VIVCOURT_ORDER_BOOK_H_

#include "messages.hpp"
#include <map>
#include <unordered_map>
#include <optional>

namespace vivcourt
{
    struct OrderBookTraits
    {
        using TriggerUpdateKey = decltype(messages::Sequence().Value());
        using Symbol = decltype(messages::Symbol().Value());
        using OrderId = decltype(messages::OrderId().Value());
        using Side = decltype(messages::Side().Value());
        using OrderVolume = decltype(messages::OrderVolume().Value());
        using OrderPrice = decltype(messages::OrderPrice().RawValue());
    };

    template <typename Traits>
    class PriceLevel
    {
    public:
        ALWAYS_INLINE void AddVolume(typename Traits::OrderVolume volume)
        {
            _total_volume += volume;
        }

        ALWAYS_INLINE void ReduceVolume(typename Traits::OrderVolume volume)
        {
            _total_volume -= volume;
        }

        ALWAYS_INLINE typename Traits::OrderVolume GetVolume()
        {
            return _total_volume;
        }

    private:
        typename Traits::OrderVolume _total_volume{};
    };


    template <typename Traits, typename Comparator>
    class Side
    {
    public:
        bool AddOrder(typename Traits::OrderId order_id, typename Traits::OrderPrice order_price, typename Traits::OrderVolume order_volume)
        {
            assert(order_volume != 0);

            auto it = _orders.find(order_id);
            if (it != _orders.end())
            {
                return false;
            }
            _orders[order_id] = std::make_pair(order_price, order_volume);
            _levels[order_price].AddVolume(order_volume);
            return true;
        }

        bool UpdateOrder(typename Traits::OrderId order_id, typename Traits::OrderPrice order_price, typename Traits::OrderVolume order_volume)
        {
            assert(order_volume != 0);

            auto oit = _orders.find(order_id);
            if (oit == _orders.end())
            {
                return false;
            }

            auto lit = _levels.find(oit->second.first);
            if (lit == _levels.end())
            {
                return false;
            }

            lit->second.ReduceVolume(oit->second.second);
            if (oit->second.first == order_price)
            {
                lit->second.AddVolume(order_volume);
            }
            else
            {
                if (lit->second.GetVolume() == 0)
                {
                    _levels.erase(lit);
                }
                _levels[order_price].AddVolume(order_volume);
            }
            oit->second.first = order_price;
            oit->second.second = order_volume;
            return true;
        }

        bool DeleteOrder(typename Traits::OrderId order_id)
        {
            auto oit = _orders.find(order_id);
            if (oit == _orders.end())
            {
                return false;
            }

            auto lit = _levels.find(oit->second.first);
            if (lit == _levels.end())
            {
                return false;
            }
            lit->second.ReduceVolume(oit->second.second);
            if (lit->second.GetVolume() == 0)
            {
                _levels.erase(lit);
            }

            _orders.erase(oit);
            return true;
        }

        bool ExecuteOrder(typename Traits::OrderId order_id, typename Traits::OrderVolume traded_volume)
        {
            auto oit = _orders.find(order_id);
            if (oit == _orders.end())
            {
                return false;
            }

            auto lit = _levels.find(oit->second.first);
            if (lit == _levels.end())
            {
                return false;
            }
            lit->second.ReduceVolume(traded_volume);
            if (lit->second.GetVolume() == 0)
            {
                _levels.erase(lit);
            }

            oit->second.second -= traded_volume;
            if (oit->second.second == 0)
            {
                _orders.erase(oit);
            }

            return true;
        }

        void ExtractDepth(std::optional<uint8_t> max_level, std::vector<std::pair<typename Traits::OrderPrice, typename Traits::OrderVolume>> &depth)
        {
            depth.clear();
            std::size_t i = 1;
            for (auto it = _levels.begin(); it != _levels.end() && (!max_level || i <= *max_level); ++i, ++it)
            {
                depth.emplace_back(it->first, it->second.GetVolume());
            }
        }

    private:
        std::map<typename Traits::OrderPrice, PriceLevel<Traits>, Comparator> _levels;
        std::unordered_map<typename Traits::OrderId, std::pair<typename Traits::OrderPrice, typename Traits::OrderVolume>> _orders;
    };

    enum class SideEnum { Bid, Ask };

    template <typename Traits>
    class OrderBook
    {
    public:
        template <SideEnum S>
        ALWAYS_INLINE auto AddOrder(typename Traits::OrderId order_id, typename Traits::OrderPrice order_price, typename Traits::OrderVolume order_volume)
        {
            if constexpr (S == SideEnum::Bid)
            {
                return _bid_side.AddOrder(order_id, order_price, order_volume);
            }
            else
            {
                return _ask_side.AddOrder(order_id, order_price, order_volume);
            }
        }

        template <SideEnum S>
        ALWAYS_INLINE auto UpdateOrder(typename Traits::OrderId order_id, typename Traits::OrderPrice order_price, typename Traits::OrderVolume order_volume)
        {
            if constexpr (S == SideEnum::Bid)
            {
                return _bid_side.UpdateOrder(order_id, order_price, order_volume);
            }
            else
            {
                return _ask_side.UpdateOrder(order_id, order_price, order_volume);
            }
        }

        template <SideEnum S>
        ALWAYS_INLINE auto DeleteOrder(typename Traits::OrderId order_id)
        {
            if constexpr (S == SideEnum::Bid)
            {
                return _bid_side.DeleteOrder(order_id);
            }
            else
            {
                return _ask_side.DeleteOrder(order_id);
            }
        }

        template <SideEnum S>
        ALWAYS_INLINE auto ExecuteOrder(typename Traits::OrderId order_id, typename Traits::OrderVolume traded_volume)
        {
            if constexpr (S == SideEnum::Bid)
            {
                return _bid_side.ExecuteOrder(order_id, traded_volume);
            }
            else
            {
                return _ask_side.ExecuteOrder(order_id, traded_volume);
            }
        }

        ALWAYS_INLINE void ExtractDepth(
            std::optional<uint8_t> max_level,
            std::vector<std::pair<typename Traits::OrderPrice, typename Traits::OrderVolume>> &bid_depth,
            std::vector<std::pair<typename Traits::OrderPrice, typename Traits::OrderVolume>> &ask_depth)
        {
            _bid_side.ExtractDepth(max_level, bid_depth);
            _ask_side.ExtractDepth(max_level, ask_depth);
        }

    private:
        Side<Traits, std::greater<typename Traits::OrderPrice>> _bid_side;
        Side<Traits, std::less<typename Traits::OrderPrice>> _ask_side;
    };

}

#endif // _VIVCOURT_ORDER_BOOK_H_
