#tests commands with comments

!#/bin/sh

echo hello#world | ./rshell

echo hello && echo there # echo world | ./rshell

echo hello there wor#ld | ./rshell

(echo A) # Hello | ./rshell
(echo A && echo B) # (echo C)| ./rshell
(echo A && echo B) || (echo C && echo D) # (echo E && echo F)| ./rshell
(echo A) && (echo B) # (each || echo D)| ./rshell
(echo A) && (echo B) && (echo C) # (ls -a)| ./rshell

[ -f orOp.cpp ] # echo A| ./rshell
test –e orOp.cpp && test –e andOp.cpp # test -d andOp.cpp | ./rshell
test –d andOp.cpp # (echo A)| ./rshell
