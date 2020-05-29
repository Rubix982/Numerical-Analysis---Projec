mkdir build
cd build
cmake .. &>> /dev/null
make &>> /dev/null
./NC
cd ..
rm -r build/