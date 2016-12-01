#tests exit and commands with exit

!#/bin/sh

exit | ./rshell

ls; exit | ./rshell

(echo A); exit | ./rshell
(echo A && echo B) ; exit | ./rshell
(echo A && echo B); exit || (echo C && echo D) | ./rshell
(echo A) && (echo B) && exit | ./rshell

[ -f orOp.cpp ] || exit | ./rshell
test –e orOp.cpp && test –e andOp.cpp ; exit | ./rshell
test –d andOp.cpp && exit | ./rshell
