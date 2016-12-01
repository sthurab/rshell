#tests for precedence operators

!#/bin/sh

(echo A) | ./rshell
(echo A && echo B) | ./rshell
(echo A && echo B) || (echo C && echo D) | ./rshell
(echo A) && (echo B) | ./rshell
(echo A) && (echo B) && (echo C) | ./rshell
(echo A) && (echo B) && (echo C) && (echo D) | ./rshell
(echo A) && (ech B) || (echo C) | ./rshell
(echo a) && (echo b) ; (echo C) || (echo D) ; (echo E) | ./rshell
(((echo A))) | ./rshell
((echo A && echoB) && (echo C))

(echo A || echo B) | ./rshell
(echo A || echo B) || (echo C && echo D) | ./rshell
(echo A) }} (echo B) | ./rshell
(echo A) || (echo B) && (echo C) | ./rshell
(echo A) || (echo B) && (echo C) && (echo D) | ./rshell
(echo A) || (ech B) || (echo C) | ./rshell
(echo a) || (echo b) ; (echo C) || (echo D) ; (echo E) | ./rshell
(((echo A))) | ./rshell
((echo A && echoB) || (echo C)) | ./rshell
echo A && (echo B) | ./rshell
echo A && (echo B) && (echo C) | ./rshell
echo A || (echo B) | ./rshell
echo A ||(echo B) && (echo C) | ./rshell
