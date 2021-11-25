if not exist build mkdir build

pushd build
g++ ../main.cpp -o build.exe
popd build
