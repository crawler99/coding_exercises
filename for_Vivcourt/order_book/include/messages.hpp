#ifndef _VIVCOURT_MESSAGES_H_
#define _VIVCOURT_MESSAGES_H_

#include "types.hpp"

namespace vivcourt::messages
{
#pragma pack(push, 1)

    using Sequence = types::UnsignedNumeric<4>;
    using MessageSize = types::UnsignedNumeric<4>;
    using Symbol = types::Alpha<3>;
    using OrderId = types::UnsignedNumeric<8>;
    using Side = types::Alpha<1>;
    using OrderVolume = types::UnsignedNumeric<8>;
    using OrderPrice = types::Price<4, 4>;

    struct Header
    {
        Sequence        _sequence;
        MessageSize     _msg_size;
    };

    struct OrderAdded
    {
        char            _msg_type;
        Symbol          _symbol;
        OrderId         _order_id;
        Side            _side;
        types::Alpha<3> _reserved1;
        OrderVolume     _order_volume;
        OrderPrice      _order_price;
        types::Alpha<4> _reserved2;
    };

    struct OrderUpdated
    {
        char            _msg_type;
        Symbol          _symbol;
        OrderId         _order_id;
        Side            _side;
        types::Alpha<3> _reserved1;
        OrderVolume     _order_volume;
        OrderPrice      _order_price;
        types::Alpha<4> _reserved2;
    };

    struct OrderDeleted
    {
        char            _msg_type;
        Symbol          _symbol;
        OrderId         _order_id;
        Side            _side;
        types::Alpha<3> _reserved1;
    };

    struct OrderExecuted
    {
        char            _msg_type;
        Symbol          _symbol;
        OrderId         _order_id;
        Side            _side;
        types::Alpha<3> _reserved1;
        OrderVolume     _traded_volume;
    };

#pragma pack(pop)
}

#endif // _VIVCOURT_MESSAGES_H_
