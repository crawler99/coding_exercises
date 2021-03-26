#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class String {

public:
  String()
  {
  }
  
  String(const char* val)
  {
    assert(val); // probably we don't want nullptr
    _len = ::strlen(val);
    _data = new char[_len + 1];
    ::memcpy(_data, val, _len);
    _data[_len] = '\0';
  }
  
  ~String()
  {
    delete [] _data;
    _data = nullptr;
  }
  
  String(const String &another)
  {
    if (another._len == 0)
    {
      return;
    }
    
    _data = new char[another._len + 1];
    ::memcpy(_data, another._data, another._len);
    _len = another._len;
    _data[_len] = '\0';
  }
  
  String& operator=(const String &another)
  {
    if (this != &another && another._len != 0)
    {
      _len = another._len;
      delete [] _data;
      _data = new char[_len + 1];
      ::memcpy(_data, another._data, _len);
      _data[_len] = '\0';
    }
    return *this;
  }
  
  String(String &&another)
  {
    _len = another._len;
    _data = another._data;
    another._data = nullptr;
  }
  
  String& operator=(String &&another)
  {
    _len = another._len;
    delete [] _data;
    _data = another._data;
    another._data = nullptr;
    return *this;
  }

  size_t size()
  {
    return _len;
  }
  
  const char* c_str()
  {
    if (_len == 0)
      return &_empty_str;
    return _data;
  }
  
private:
  size_t _len {0};
  char *_data {nullptr};
  char _empty_str{};
};

String MoveString(String src)
{
  return src;
}

int main() 
{
  String a{"hello, world"};
  String b(std::move(a));
  String c = MoveString(b); 
  return 0;
}

