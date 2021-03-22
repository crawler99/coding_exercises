#ifndef _VIVCOURT_MESSAGES_H_
#define _VIVCOURT_MESSAGES_H_

#include "types.hpp"

namespace vivcourt::messages
{
#pragma pack(push, 1)

    struct TypeTraits
    {
        using Symbol = decltype(types::Alpha<3>().Value());
        using OrderId = decltype(types::UnsignedNumeric<8>().Value());
        using Side = decltype(types::Alpha<1>().Value());
        using OrderVolume = decltype(types::UnsignedNumeric<8>().Value());
        using OrderPrice = decltype(types::Price<4, 4>().RawValue());
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
