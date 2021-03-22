#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "messages.hpp"

TEST(OrderBook, numeric_types)
{
    int8_t i8_1 = 123;
    int8_t i8_2 = 0;
    int8_t i8_3 = -45;
    auto *si8_1 = reinterpret_cast<vivcourt::types::SignedNumeric<1>*>(&i8_1);
    EXPECT_EQ(si8_1->Value(), i8_1);
    auto *si8_2 = reinterpret_cast<vivcourt::types::SignedNumeric<1>*>(&i8_2);
    EXPECT_EQ(si8_2->Value(), i8_2);
    auto *si8_3 = reinterpret_cast<vivcourt::types::SignedNumeric<1>*>(&i8_3);
    EXPECT_EQ(si8_3->Value(), i8_3);

    uint8_t u8_1 = 123;
    uint8_t u8_2 = 0;
    auto *su8_1 = reinterpret_cast<vivcourt::types::UnsignedNumeric<1>*>(&u8_1);
    EXPECT_EQ(su8_1->Value(), u8_1);
    auto *su8_2 = reinterpret_cast<vivcourt::types::UnsignedNumeric<1>*>(&u8_2);
    EXPECT_EQ(su8_2->Value(), u8_2);

    int16_t i16_1 = 12345;
    int16_t i16_2 = 0;
    int16_t i16_3 = -23456;
    auto *si16_1 = reinterpret_cast<vivcourt::types::SignedNumeric<2>*>(&i16_1);
    EXPECT_EQ(si16_1->Value(), i16_1);
    auto *si16_2 = reinterpret_cast<vivcourt::types::SignedNumeric<2>*>(&i16_2);
    EXPECT_EQ(si16_2->Value(), i16_2);
    auto *si16_3 = reinterpret_cast<vivcourt::types::SignedNumeric<2>*>(&i16_3);
    EXPECT_EQ(si16_3->Value(), i16_3);

    uint16_t u16_1 = 12345;
    uint16_t u16_2 = 0;
    auto *su16_1 = reinterpret_cast<vivcourt::types::UnsignedNumeric<2>*>(&u16_1);
    EXPECT_EQ(su16_1->Value(), u16_1);
    auto *su16_2 = reinterpret_cast<vivcourt::types::UnsignedNumeric<2>*>(&u16_2);
    EXPECT_EQ(su16_2->Value(), u16_2);

    int32_t i32_1 = 1073741824;
    int32_t i32_2 = 0;
    int32_t i32_3 = -858993459;
    auto *si32_1 = reinterpret_cast<vivcourt::types::SignedNumeric<4>*>(&i32_1);
    EXPECT_EQ(si32_1->Value(), i32_1);
    auto *si32_2 = reinterpret_cast<vivcourt::types::SignedNumeric<4>*>(&i32_2);
    EXPECT_EQ(si32_2->Value(), i32_2);
    auto *si32_3 = reinterpret_cast<vivcourt::types::SignedNumeric<4>*>(&i32_3);
    EXPECT_EQ(si32_3->Value(), i32_3);

    uint32_t u32_1 = 1073741824;
    uint32_t u32_2 = 0;
    auto *su32_1 = reinterpret_cast<vivcourt::types::UnsignedNumeric<4>*>(&u32_1);
    EXPECT_EQ(su32_1->Value(), u32_1);
    auto *su32_2 = reinterpret_cast<vivcourt::types::UnsignedNumeric<4>*>(&u32_2);
    EXPECT_EQ(su32_2->Value(), u32_2);

    int64_t i64_1 = 4611686018427387904;
    int64_t i64_2 = 0;
    int64_t i64_3 = -2305843009213693952;
    auto *si64_1 = reinterpret_cast<vivcourt::types::SignedNumeric<8>*>(&i64_1);
    EXPECT_EQ(si64_1->Value(), i64_1);
    auto *si64_2 = reinterpret_cast<vivcourt::types::SignedNumeric<8>*>(&i64_2);
    EXPECT_EQ(si64_2->Value(), i64_2);
    auto *si64_3 = reinterpret_cast<vivcourt::types::SignedNumeric<8>*>(&i64_3);
    EXPECT_EQ(si64_3->Value(), i64_3);

    uint64_t u64_1 = 4611686018427387904;
    uint64_t u64_2 = 0;
    auto *su64_1 = reinterpret_cast<vivcourt::types::UnsignedNumeric<8>*>(&u64_1);
    EXPECT_EQ(su64_1->Value(), u64_1);
    auto *su64_2 = reinterpret_cast<vivcourt::types::UnsignedNumeric<8>*>(&u64_2);
    EXPECT_EQ(su64_2->Value(), u64_2);
}

TEST(OrderBook, price_type)
{
    int32_t price1 = 12;
    int32_t price2 = 1234;
    int32_t price3 = 123456;
    int32_t price4 = 0;
    int32_t price5 = -12;
    int32_t price6 = -1234;
    int32_t price7 = -123456;

    auto *sprice1 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price1);
    EXPECT_EQ(sprice1->RawValue(), price1);
    EXPECT_DOUBLE_EQ(sprice1->Value(), 0.0012);
    auto *sprice2 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price2);
    EXPECT_EQ(sprice2->RawValue(), price2);
    EXPECT_DOUBLE_EQ(sprice2->Value(), 0.1234);
    auto *sprice3 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price3);
    EXPECT_EQ(sprice3->RawValue(), price3);
    EXPECT_DOUBLE_EQ(sprice3->Value(), 12.3456);
    auto *sprice4 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price4);
    EXPECT_EQ(sprice4->RawValue(), price4);
    EXPECT_DOUBLE_EQ(sprice4->Value(), 0.0);
    auto *sprice5 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price5);
    EXPECT_EQ(sprice5->RawValue(), price5);
    EXPECT_DOUBLE_EQ(sprice5->Value(), -0.0012);
    auto *sprice6 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price6);
    EXPECT_EQ(sprice6->RawValue(), price6);
    EXPECT_DOUBLE_EQ(sprice6->Value(), -0.1234);
    auto *sprice7 = reinterpret_cast<vivcourt::types::Price<4, 4>*>(&price7);
    EXPECT_EQ(sprice7->RawValue(), price7);
    EXPECT_DOUBLE_EQ(sprice7->Value(), -12.3456);
}

TEST(OrderBook, alpha_type)
{
    char str1[] = "hello,world"; // 11 chars
    char str2[] = "hello,     ";
    char str3[] = "           ";

    auto *alpha1 = reinterpret_cast<vivcourt::types::Alpha<11>*>(str1);
    EXPECT_EQ(alpha1->Value().compare(str1), 0);
    auto *alpha2 = reinterpret_cast<vivcourt::types::Alpha<11>*>(str2);
    EXPECT_EQ(alpha2->Value().compare("hello,"), 0);
}