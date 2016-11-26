#tests exit and commands with exit

exit #just exit
echo A && exit #A
echo A || exit #A, testdone
echo A; exit #A
echo A #exit #A, testdone


(echo A); exit #A
