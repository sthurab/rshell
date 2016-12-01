#tests for the test command

!#/bin/sh

test –e andOp.cpp | ./rshell
test –e orOp.cpp && test –e andOp.cpp | ./rshell
[ -e orOp.cpp ] | ./rshell
[ orOp.cpp ] | ./rshell

test –f andOp.cpp | ./rshell
test –f orOp.cpp && test –e andOp.cpp | ./rshell
[ -f orOp.cpp ] | ./rshell

test –d andOp.cpp | ./rshell
test –d orOp.cpp && test –e andOp.cpp | ./rshell
[ -d orOp.cpp ] | ./rshell
