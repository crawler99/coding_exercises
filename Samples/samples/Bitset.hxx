#pragma once

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#else
#define FORCE_INLINE 
#endif

#include <limits>
#include <cstring>
#include <stdexcept>

// --------------------------------------------------------
// This is a class to hold a bit set data structure.
// --------------------------------------------------------
template <size_t SIZE>
class Bitset
{
public:
    using BlockType = unsigned long;  // actually the underneath block-storage type can be templated as well
    using SizeType = decltype(SIZE);

    // Ctor
    Bitset() : _bitNum(SIZE) 
    {
#ifdef DEBUG
        std::cout << "\nIn constructor";
#endif
        auto freeBits = (_blockBits - _bitNum % _blockBits);
        _blockNum = _bitNum / _blockBits + (freeBits == 0 ? 0 : 1);
        _pBits = new BlockType[_blockNum];  // in case of failure, std::bad_alloc will be thrown for caller to catch
        memset(_pBits, 0, _blockNum * _blockBytes);
    }

    // Copy ctor
    Bitset(const Bitset<SIZE> &val)
    {
#ifdef DEBUG
        std::cout << "\nIn copy constructor";
#endif
        _bitNum = val._bitNum;
        _blockNum = val._blockNum;
        _pBits = new BlockType[_blockNum];  // in case of failure, std::bad_alloc will be thrown for caller to catch
        memcpy(_pBits, val._pBits, _blockNum * _blockBytes);
    }

    // Copy assignment operator with copy-and-swap idiom (don't need to define move assignment operator as this one takes over)
    friend void swap(Bitset<SIZE> &first, Bitset<SIZE> &second)
    {
        using std::swap;
	swap(first._pBits, second._pBits);
	swap(first._bitNum, second._bitNum);
	swap(first._blockNum, second._blockNum);
    }

    Bitset& operator = (Bitset<SIZE> another)
    {
#ifdef DEBUG
        std::cout << "\nIn copy assignment operator";
#endif
        swap(*this, another);
        return (*this);
    }

    // Move ctor
    Bitset(Bitset<SIZE> &&another) : Bitset()
    {
#ifdef DEBUG
        std::cout << "\nIn move constructor";
#endif
	swap(*this, another);
    }

    // Dtor
    ~Bitset()
    {
        delete [] _pBits;  // even deleting a null pointer is fine
    }

    // Get size
    SizeType getSize() const noexcept FORCE_INLINE
    {
        return _bitNum;
    }

    // Reset all the bits to 0
    void reset() noexcept FORCE_INLINE
    {
        memset(_pBits, 0, _blockNum * _blockBytes);
    }

    // Return true if the given bit is set, false otherwise
    bool isSet(SizeType pos) const FORCE_INLINE
    {
        _checkPos(pos);
        return _pBits[pos / _blockBits] & (1 << (pos % _blockBits));
    }

    // Sets the given bit in the bit set and return the old value of the bit
    bool set(SizeType pos) FORCE_INLINE
    {
        _checkPos(pos);
        auto blockIdx = pos / _blockBits;
        auto bitIdx = pos % _blockBits;
        auto old = _pBits[blockIdx] & (1 << bitIdx);
        _pBits[blockIdx] |= (1 << bitIdx);
        return old;
    }

    // Clears the given bit in the bit set and return the old value of the bit
    bool clear(SizeType pos) FORCE_INLINE
    {
        _checkPos(pos);
        auto blockIdx = pos / _blockBits;
        auto bitIdx = pos % _blockBits;
        auto old = _pBits[blockIdx] & (1 << bitIdx);
        _pBits[blockIdx] &= ~(1 << bitIdx);
        return old;
    }

    // Inverts the given bit in the bit set and return the old value of the bit
    bool invert(SizeType pos) FORCE_INLINE
    {
        _checkPos(pos);
        auto blockIdx = pos / _blockBits;
        auto bitIdx = pos % _blockBits;
        auto old = _pBits[blockIdx] & (1 << bitIdx);
        _pBits[blockIdx] ^= (1 << bitIdx);
        return old;
    }

private:
    void _checkPos(SizeType pos) const FORCE_INLINE
    {
        if (pos > _bitNum)
        {
            throw std::invalid_argument("Invalid position");
        }
    }

    // Constants
    uint8_t     _blockBits = std::numeric_limits<BlockType>::digits;
    uint8_t     _blockBytes = sizeof(BlockType);

    // Storage
    BlockType  *_pBits     { nullptr };  // to hold a large-enough bit set I need to allocate mem on heap
    SizeType    _bitNum;
    SizeType    _blockNum;
};

