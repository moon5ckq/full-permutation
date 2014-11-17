#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 mlckq <moon5ckq@gmail.com>
#
# Distributed under terms of the MIT license.

"""
random a permutation
"""
import sys, random

if __name__ == '__main__':
    if len(sys.argv) < 1:
        sys.exit('usage: %s <n>' % sys.argv[0])
    n = int(sys.argv[1])
    s = range(1, n + 1)
    while True:
        random.shuffle(s)
        if s[0] != n:
            break
    print ' '.join(map(str, s))
