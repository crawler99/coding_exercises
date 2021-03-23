#ifndef _VIVCOURT_ORDER_BOOK_MANAGER_H_
#define _VIVCOURT_ORDER_BOOK_MANAGER_H_

#include "messages.hpp"
#include "order_book.hpp"
#include <iostream>

namespace vivcourt
{
    struct OrderBookTraits
    {
        using Symbol = decltype(messages::Symbol().Value());
        using OrderId = decltype(messages::OrderId().Value());
        using Side = decltype(messages::Side().Value());
        using OrderVolume = decltype(messages::OrderVolume().Value());
        using OrderPrice = decltype(messages::OrderPrice().RawValue());
    };

    struct DepthUpdate
    {
        decltype(messages::Sequence().Value()) _update_seq;
        typename OrderBookTraits::Symbol _symbol;
        std::vector<std::pair<typename OrderBookTraits::OrderPrice, typename OrderBookTraits::OrderVolume>> _bid_depth;
        std::vector<std::pair<typename OrderBookTraits::OrderPrice, typename OrderBookTraits::OrderVolume>> _ask_depth;
    };

    std::ostream& operator<<(std::ostream &os, const DepthUpdate &depth_update)
    {
        os << depth_update._update_seq << ", " << depth_update._symbol << ", [";
        for (std::size_t i = 0; i < depth_update._bid_depth.size(); ++i)
        {
            auto &level = depth_update._bid_depth[i];
            os << (i == 0 ? "" : ", ") << "(" << level.first << ", " << level.second << ")";
        }
        os << "], [";
        for (std::size_t i = 0; i < depth_update._ask_depth.size(); ++i)
        {
            auto &level = depth_update._ask_depth[i];
            os << (i == 0 ? "" : ", ") << "(" << level.first << ", " << level.second << ")";
        }
        os << "]";
        return os;
    }

    class OrderBookManager
    {
    public:
        std::optional<DepthUpdate> ProcessOrderAdded(const messages::Header &header, messages::OrderAdded &msg)
        {
            auto &book = _books[msg._symbol.Value()];
            book.SetReportDepth(_report_depth);
            auto side_enum = GetSide(msg._side);
            auto old_depth = book.GetDepth(side_enum);
            if (!book.AddOrder(side_enum, msg._order_id.Value(), msg._order_price.RawValue(), msg._order_volume.Value()))
            {
                return std::nullopt;
            }

            auto new_depth = book.GetDepth(side_enum);
            if (old_depth != new_depth)
            {
                return (side_enum == SideEnum::Bid) ? DepthUpdate{header._sequence.Value(), msg._symbol.Value(), new_depth, book.GetDepth(SideEnum::Ask)}
                                                    : DepthUpdate{header._sequence.Value(), msg._symbol.Value(), book.GetDepth(SideEnum::Bid), new_depth};
            }
            return std::nullopt;
        }

        std::optional<DepthUpdate> ProcessOrderUpdated(const messages::Header &header, const messages::OrderUpdated &msg)
        {
            auto it = _books.find(msg._symbol.Value());
            if (it == _books.end())
            {
                return std::nullopt;
            }

            auto &book = it->second;
            auto side_enum = GetSide(msg._side);
            auto old_depth = book.GetDepth(side_enum);
            if (!it->second.UpdateOrder(side_enum, msg._order_id.Value(), msg._order_price.RawValue(), msg._order_volume.Value()))
            {
                return std::nullopt;
            }

            auto new_depth = book.GetDepth(side_enum);
            if (old_depth != new_depth)
            {
                return (side_enum == SideEnum::Bid) ? DepthUpdate{header._sequence.Value(), msg._symbol.Value(), new_depth, book.GetDepth(SideEnum::Ask)}
                                                    : DepthUpdate{header._sequence.Value(), msg._symbol.Value(), book.GetDepth(SideEnum::Bid), new_depth};
            }
            return std::nullopt;
        }

        std::optional<DepthUpdate> ProcessOrderDeleted(const messages::Header &header, const messages::OrderDeleted &msg)
        {
            auto it = _books.find(msg._symbol.Value());
            if (it == _books.end())
            {
                return std::nullopt;
            }

            auto &book = it->second;
            auto side_enum = GetSide(msg._side);
            auto old_depth = book.GetDepth(side_enum);
            if (!it->second.DeleteOrder(side_enum, msg._order_id.Value()))
            {
                return std::nullopt;
            }

            auto new_depth = book.GetDepth(side_enum);
            if (old_depth != new_depth)
            {
                return (side_enum == SideEnum::Bid) ? DepthUpdate{header._sequence.Value(), msg._symbol.Value(), new_depth, book.GetDepth(SideEnum::Ask)}
                                                    : DepthUpdate{header._sequence.Value(), msg._symbol.Value(), book.GetDepth(SideEnum::Bid), new_depth};
            }
            return std::nullopt;
        }

        std::optional<DepthUpdate> ProcessOrderExecuted(const messages::Header &header, const messages::OrderExecuted &msg)
        {
            auto it = _books.find(msg._symbol.Value());
            if (it == _books.end())
            {
                return std::nullopt;
            }

            auto &book = it->second;
            auto side_enum = GetSide(msg._side);
            auto old_depth = book.GetDepth(side_enum);
            if (!it->second.ExecuteOrder(side_enum, msg._order_id.Value(), msg._traded_volume.Value()))
            {
                return std::nullopt;
            }

            auto new_depth = book.GetDepth(side_enum);
            if (old_depth != new_depth)
            {
                return (side_enum == SideEnum::Bid) ? DepthUpdate{header._sequence.Value(), msg._symbol.Value(), new_depth, book.GetDepth(SideEnum::Ask)}
                                                    : DepthUpdate{header._sequence.Value(), msg._symbol.Value(), book.GetDepth(SideEnum::Bid), new_depth};
            }
            return std::nullopt;
        }

        ALWAYS_INLINE OrderBookManager& SetReportDepth(std::optional<uint8_t> report_depth)
        {
            _report_depth = report_depth;
            return *this;
        }

    private:
        ALWAYS_INLINE SideEnum GetSide(const messages::Side &msg_side)
        {
            return (msg_side.Value() == "B" ? SideEnum::Bid : SideEnum::Ask);
        }

        std::optional<uint8_t> _report_depth;
        std::unordered_map<std::string, OrderBook<OrderBookTraits>> _books;
    };

}

#endif // _VIVCOURT_ORDER_BOOK_MANAGER_H_
