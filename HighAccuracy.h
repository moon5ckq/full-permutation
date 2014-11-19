/*
 * Author: mlckq <moon5ckq@gmail.com>
 * File: HighAccuracy.h
 * Create Date: 2014-11-14 15:47
 */

#ifndef __HIGHACCURACY_H__
#define __HIGHACCURACY_H__

#include <cstdint>
#include <string>
#include <vector>

#define CAP_SIZE 10000
#define BASE 0x7fffffff
#define BASEV 0x80000000
#define POWER 31

class HighAccuracy {
public:
    HighAccuracy(int num = 0);
    HighAccuracy(const char* str);
    HighAccuracy(const std::string& str);
    void load(const char* str);
    void load(const std::string& str);
    std::string str() const;

    inline int32_t& operator[](int index) {
        return _num[index];
    }
    inline int32_t operator[](int index) const {
        return _num[index];
    }
    inline int len() const {
        return static_cast<int>(_num.size());
    }
    inline int32_t div(int32_t x) {
        return _div(x);
    }

    HighAccuracy& operator*= (int32_t x);
    HighAccuracy& operator/= (int32_t x);
    HighAccuracy& operator+= (const HighAccuracy& x);
    HighAccuracy& operator-= (const HighAccuracy& x);
    friend HighAccuracy operator* (const HighAccuracy& u, int32_t x);
    friend HighAccuracy operator/ (const HighAccuracy& u, int32_t x);
    friend HighAccuracy operator+ (const HighAccuracy& u, const HighAccuracy& x);
    friend HighAccuracy operator- (const HighAccuracy& u, const HighAccuracy& x);
    friend int32_t SimpleDiv(const HighAccuracy& u, const HighAccuracy& v);
    friend bool operator> (const HighAccuracy& u, const HighAccuracy& v);
    friend bool operator>= (const HighAccuracy& u, const HighAccuracy& v);
    friend bool operator== (const HighAccuracy& u, const HighAccuracy& v);
    friend bool operator< (const HighAccuracy& u, const HighAccuracy& v);
    friend bool operator<= (const HighAccuracy& u, const HighAccuracy& v);
    
private:
    std::vector<int32_t> _num;
    int _compare(const HighAccuracy& x) const;
    int32_t _div(int32_t x);
};

#endif /* !__HIGHACCURACY_H__ */

