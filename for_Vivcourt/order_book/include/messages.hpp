#ifndef _VIVCOURT_MESSAGES_H_
#define _VIVCOURT_MESSAGES_H_

#include "types.hpp"

namespace vivcourt::messages
{
#pragma pack(push, 1)

    struct TypeTraits
    {
        using Symbol = types::Alpha<3>;
        static_assert(sizeof(Symbol) == 3);

        using OrderId = types::UnsignedNumeric<8>;
        static_assert(sizeof(OrderId) == 8);

        using Side = types::Alpha<1>;
        static_assert(sizeof(Side) == 1);

        using OrderVolume = types::UnsignedNumeric<8>;
        static_assert(sizeof(OrderVolume) == 8);

        using OrderPrice = types::Price<4, 4>;
        static_assert(sizeof(OrderPrice) == 4);
    };

    struct Header
    {
        types::UnsignedNumeric<4> _sequence;
        types::UnsignedNumeric<4> _msg_size;
    };

    struct OrderAdded
    {
        char                    _type;
        TypeTraits::Symbol      _symbol;
        TypeTraits::OrderId     _order_id;
        TypeTraits::Side        _side;
        types::Alpha<3>         _reserved1;
        TypeTraits::OrderVolume _order_volume;
        TypeTraits::OrderPrice  _order_price;
        types::Alpha<4>         _reserved2;
    };

    struct OrderUpdated
    {
        char                    _type;
        TypeTraits::Symbol      _symbol;
        TypeTraits::OrderId     _order_id;
        TypeTraits::Side        _side;
        types::Alpha<3>         _reserved1;
        TypeTraits::OrderVolume _order_volume;
        TypeTraits::OrderPrice  _order_price;
        types::Alpha<4>         _reserved2;
    };

    struct OrderDeleted
    {
        char                    _type;
        TypeTraits::Symbol      _symbol;
        TypeTraits::OrderId     _order_id;
        TypeTraits::Side        _side;
        types::Alpha<3>         _reserved1;
    };

    struct OrderExecuted
    {
        char                    _type;
        TypeTraits::Symbol      _symbol;
        TypeTraits::OrderId     _order_id;
        TypeTraits::Side        _side;
        types::Alpha<3>         _reserved1;
        TypeTraits::OrderVolume _traded_volume;
    };

#pragma pack(pop)
}

#endif // _VIVCOURT_MESSAGES_H_
