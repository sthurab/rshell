#tests commands with comments

echo A && echo B
echo A || echo B
echo A; echo B
ls -j && echo A
ls -j || echo A
ls -j; echo A
ls -j && echo A || echo B
echo A || echo B || echo C
echo A || echo B && echo C
echo A && echo B && echo C  # print A, B, C

echo One && echo Two # && echo Three
