# logzmq
## Build
### Linux (Debian)
```
sudo apt-get install libzmq3-dev
git clone https://github.com/k5c7/logzmq.git
cd logzmq
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
