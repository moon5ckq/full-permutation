/*
 * Author: mlckq <moon5ckq@gmail.com>
 * File: HighAccuracy.cpp
 * Create Date: 2014-11-14 16:07
 */

#include "HighAccuracy.h"
#include <cstdlib>

#include <cstdio>

using std::string;
using std::vector;

HighAccuracy::HighAccuracy(int num/*=0*/) {
    _num.reserve(CAP_SIZE);
    if (! num) return;
    _num.resize(1);
    if (num > BASE) {
        _num.resize(2);
        _num[1] = num >> POWER;
    }
    _num[0] = num & BASE;
}

HighAccuracy::HighAccuracy(const char* str) {
    _num.reserve(CAP_SIZE);
    load(str);
}

HighAccuracy::HighAccuracy(const string& str) {
    _num.reserve(CAP_SIZE);
    load(str.c_str());
}

void HighAccuracy::load(const char* str) {
    char num[10];
    int32_t ten[10] = {10};
    for (int i = 1; i < 10; ++i)
        ten[i] = ten[i-1] * 10;
    for (int i = 0; ; i += 9) {
        int j = 0;
        for (;j < 9 && str[i+j]; ++j)
            num[j] = str[i+j];
        num[j] = '\0';

        int32_t x = static_cast<int32_t>(atoi(num));
        this->operator*= (ten[j-1]);
        this->operator+= (x);

        if (!str[i+j]) break;
    }
}

string HighAccuracy::str() const {
    if (!len()) return "0";
    string ret;
    HighAccuracy u = *this;
    char tmp[10];
    while (u.len()) {
        int32_t rest = u._div(1000000000);
        sprintf(tmp, "%d", rest);
        ret = tmp + ret;
    }
    return ret;
}

void HighAccuracy::load(const string& str) {
    load(str.c_str());
}

HighAccuracy& HighAccuracy::operator*= (int32_t x) {
    int n = len();
    int64_t multipr = x, over = 0;

    for (int i = 0; i < n; ++i) {
        int64_t value = _num[i] * multipr + over;
        _num[i] = value & BASE;
        over = value >> POWER;
    }
    if (over)
        _num.push_back(static_cast<int32_t>(over));

    return *this;
}

int32_t HighAccuracy::_div(int32_t x) {
    int n = len();
    int64_t rest = 0;
    for (int i = n - 1; i >= 0; --i) {
        int64_t value = (rest << POWER) + _num[i];
        lldiv_t res = lldiv(value, x);
        _num[i] = static_cast<int32_t>(res.quot);
        rest = res.rem;
    }
    while (n > 0 && ! _num[n-1])
        --n;
    _num.resize(n);
    return static_cast<int32_t>(rest);
}

HighAccuracy& HighAccuracy::operator/= (int32_t x) {
    _div(x);
    return *this;
}

HighAccuracy& HighAccuracy::operator+= (const HighAccuracy& x) {
    int n = len(), m = x.len();
    if (n < m) {
        n = m;
        _num.resize(n);
    }
    int64_t over = 0;
    for (int i = 0; i < m; ++i) {
        int64_t value = over + _num[i] + x._num[i];
        _num[i] = static_cast<int32_t>(value & BASE);
        over = value >> POWER;
    }
    if (over)
        for (int i = m; over && i < n; ++i) {
            over += _num[i];
            _num[i] = static_cast<int32_t>(over & BASE);
            over >>= POWER;
        }
    if (over)
        _num.push_back(static_cast<int32_t>(over));
    return *this;
}

HighAccuracy& HighAccuracy::operator-= (const HighAccuracy& x) {
    int n = len(), m = x.len();
    int64_t over = 0;
    for (int i = 0; i < m; ++i) {
        over += x._num[i];
        if (_num[i] < over) {
            _num[i] = static_cast<int32_t>(static_cast<int64_t>(BASEV) +
                    _num[i] - over);
            over = 1;
        } else {
            _num[i] -= static_cast<int32_t>(over);
            over = 0;
        }
    }
    if (over) _num[m] -= 1;
    while (n > 0 && ! _num[n-1])
        --n;
    _num.resize(n);
    return *this;
}

HighAccuracy operator* (const HighAccuracy& u, int32_t x) {
    HighAccuracy v = u;
    v *= x;
    return v;
}

HighAccuracy operator/ (const HighAccuracy& u, int32_t x) {
    HighAccuracy v = u;
    v /= x;
    return v;
}

HighAccuracy operator+ (const HighAccuracy& u, const HighAccuracy& x) {
    HighAccuracy v = u;
    v += x;
    return v;
}

HighAccuracy operator- (const HighAccuracy& u, const HighAccuracy& x) {
    HighAccuracy v = u;
    v -= x;
    return v;
}

int HighAccuracy::_compare(const HighAccuracy& x) const {
    int n = len(), m = x.len();
    if (n > m) return 1;
    else if (n < m) return -1;
    for (int i = n-1; i >=0; --i)
        if (_num[i] > x._num[i]) return 1;
        else if (_num[i] < x._num[i]) return -1;
    return 0;
}

bool operator> (const HighAccuracy& u, const HighAccuracy& v) {
    return u._compare(v) == 1;
}

bool operator>= (const HighAccuracy& u, const HighAccuracy& v) {
    return u._compare(v) >= 0;
}

bool operator== (const HighAccuracy& u, const HighAccuracy& v) {
    return u._compare(v) == 0;
}

bool operator< (const HighAccuracy& u, const HighAccuracy& v) {
    return u._compare(v) == -1;
}

bool operator<= (const HighAccuracy& u, const HighAccuracy& v) {
    return u._compare(v) <= 0;
}

int32_t SimpleDiv(const HighAccuracy& u, const HighAccuracy& v) {
    int n = u.len(), m = v.len();
    if (!n) return 0;
    if (!m) return -1;

    int64_t U, V;
    if (n == m)
        if (n > 1) {
            U = (static_cast<int64_t>(u[n-1]) << POWER) | u[n-2];
            V = (static_cast<int64_t>(v[m-1]) << POWER) | v[m-2];
        } else {
            U = static_cast<int64_t>(u[n-1]);
            V = static_cast<int64_t>(v[m-1]);
        }
    else if (n == m + 1) {
        U = (static_cast<int64_t>(u[n-1]) << POWER) | u[n-2];
        V = static_cast<int64_t>(v[m-1]);
    } else if (m == n + 1) {
        U = static_cast<int64_t>(u[n-1]);
        V = (static_cast<int64_t>(v[m-1]) << POWER) | v[m-2];
    } else
        return -1;

    int32_t l = static_cast<int32_t>(U / (V+1)),
            r = static_cast<int32_t>((U+1) / V) + 1;
    while (l+1 < r) {
        int32_t mid = (l + r) >> 1;
        if (v * mid <= u) l = mid;
        else r = mid;
    }

    return l;
}
