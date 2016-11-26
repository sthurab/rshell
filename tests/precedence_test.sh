#tests for precedence operators

(echo A && echo B) || (echo C && echo D)
echo A && echo B || echo C && echo D

(echo A) && (echo B) && (echo C) || (echo D)
((echo A && echo B) || (echo C))
(echo A) || ((echo B) || (echo C))
