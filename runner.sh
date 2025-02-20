clear
rm -rf build
mkdir build && cd build
export CFLAGS="$(pkg-config --cflags glib-2.0)"
export LDFLAGS="$(pkg-config --libs glib-2.0)"
echo $CFLAGS
echo $LDFLAGS
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
./mediaFilesManager