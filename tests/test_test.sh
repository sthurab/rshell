#tests for the test command

test -e andOp.cpp && echo "path exists"
test -e orOp.cpp && echo "path exists"
test -f andOp.cpp && echo "it is a  regular file"
test -f orOp.cpp && echo "it is a  regular file"

test -d orOp.cpp && echo "it is not a directory"
