% complexity.m
% Copyright (C) 2014 mlckq <moon5ckq@gmail.com>
% 
% Distributed under terms of the MIT license.
% ¸´ÔÓ¶Èº¯Êý

x = [1, 10:10:100000]';
y = x .* x .* log(x) / 21.4875;
figure(2);
plot(x, y);
