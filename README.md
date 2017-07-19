# QCalculateServer
Receives from the client expressions in infix notation, and returns the computed result
instalation:
mkdir cmake-build-debug

cd cmake-build-debug/

cmake ..

make..

./QCalculateServer -t start -p 7777 -a any -m 30
