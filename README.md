# dcps_temp

### better way (make a mirror directory)
mkdir build
cp src* ./build
mwc.pl -type gnuace
make

# generate clion config file
compiledb -nf make
