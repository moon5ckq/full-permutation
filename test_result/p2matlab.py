#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2014 mlckq <moon5ckq@gmail.com>
#
# Distributed under terms of the MIT license.

"""
a python script to change the data to a matlab program for draw some plots

"""
import sys
color = ['1 0 0', '0 1 0', '0 0 1', '0 0 0', '1 0.5 0.5', '0.5 1 0.5', '0.5 0.5 1', '0.5 0.5 0.5']

print \
'''% complexity.m
% Copyright (C) 2014 mlckq <moon5ckq@gmail.com>
% 
% Distributed under terms of the MIT license.
% 实验结果

figure(1);
'''

with open(sys.argv[1]) as f:
    r = {}
    for line in f:
        x = line.strip().split()
        v = str(x[1]) + str(x[2])
        if v not in r:
            r[v] = []
        r[v].append( (x[0], x[3]) )

    for i, (k, v) in enumerate(r.items()):
        print 'x_%s = ['%k,
        print ','.join(map(lambda x:x[0], v)), 
        print '];'

        print 'y_%s = ['%k,
        print ','.join(map(lambda x:x[1], v)), 
        print '];'

        print 'plot(x_%s, y_%s, \'Color\', [%s]); hold on;'%(k, k, color[i])
