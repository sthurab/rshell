!#/bin/sh

cd | ./rshell
cd - | ./rshell
cd check | ./rshell
cd DoesNotExist | ./rshell
cd check; cd - | ./rshell
cd check; cd -; cd - | ./rshell
cd check && echo A | ./rshell
cd DoesNotExist && echo A | ./rshell
cd check || echo A | ./rshell
cd DoesNotExist || echo A | ./rshell
cd check .. ; cd src ; cd | ./rshell
(cd) | ./rshell
(cd && echo A) | ./rshell
(cd -) | ./rshell
