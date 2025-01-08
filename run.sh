# Handy run.sh script to clean, build and run the project

rm -rf build

mkdir build && cd build

cmake ..

cmake --build .

./porcelain | ./wav-write