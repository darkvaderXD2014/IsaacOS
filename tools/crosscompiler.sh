#!/bin/bash

# Made by: Ian Sapelino

errType=0


if [ `whoami` != "root" ]; then
	echo "Unable to download. Please run as administrator."
	exit	
fi

BINUTILSURL="https://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.gz"
GCCURL="ftp://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz"
GMPURL="https://gmplib.org/download/gmp/gmp-6.1.2.tar.lz"
MPFRURL="http://www.mpfr.org/mpfr-current/mpfr-4.0.1.tar.xz"
MPCURL="https://ftp.gnu.org/gnu/mpc/mpc-1.1.0.tar.gz"

echo "Downloading the cross-compilers."

PREFIX="/usr/local/cross"
TARGET="i686-elf"
PATH="$PREFIX/bin:$PATH"

if [ -d "/usr/local/src" ]; then
	echo "Directory /usr/local/src is found."
	sleep 2s
	else
	echo "Directory /usr/local/src is not found. Making a new directory."
	sleep 2s
	mkdir -v /usr/local/src
fi

cd /usr/local/src

if [ -d build-binutils ]; then
	echo "Folder has already been exist, removing its excess."
	rm -rf build-binutils/*
else
	echo "Making the directory."
	mkdir -v build-binutils
fi

if [ -d build-gcc ]; then
	echo "Folder has already been exist, removing its excess."
	rm -rf build-gcc/*
else
	echo "Making the directory!"
	mkdir -v build-gcc
fi

if [ -f `basename $BINUTILSURL` ]; then
echo "Binutils has already exist, skipping this part."
#rm -rf `basename $BINUTILSURL .tar.gz`
echo "Extracting the compressed file!"
tar xvf `basename $BINUTILSURL`
else
echo "Downloading Binutils 2.22"
wget -c $BINUTILSURL
sleep 3s
echo "Extracting the compressed file!"
tar xvf `basename $BINUTILSURL`
fi

if [ -f `basename $GCCURL` ]; then
echo "GCC has already exists, skipping this part."
#rm -rf `basename $GCCURL .tar.bz2`
tar xvf `basename $GCCURL`
else
echo "Downloading GCC 4.9.0... :)"
wget -c $GCCURL
sleep 3s
echo "Extracting the compressed file!"
tar xvf `basename $GCCURL`
fi 

if [ -f `basename $GMPURL` ]; then
echo "GMP has already exists, skipping this part."
#rm -rf `basename $GMPURL .tar.lz`
tar xvf `basename $GMPURL`
else
echo "Downloading GMP for GCC... :)"
wget -c $GMPURL
sleep 3s
echo "Extracting the compressed file!"
tar xvf `basename $GMPURL`
fi 

if [ -f `basename $MPFRURL` ]; then
echo "GCC has already exists, skipping this part."
#rm -rf `basename $MPFRURL .tar.xz`
tar xvf `basename $MPFRURL`
else
echo "Downloading MPFR for GCC.. :)"
wget -c $MPFRURL
sleep 3s
echo "Extracting the compressed file!"
tar xvf `basename $MPFRURL`
fi 

if [ -f `basename $MPCURL` ]; then
echo "GCC has already exists, skipping this part."
#rm -rf `basename $MPCURL .tar.gz`
tar xvf `basename $MPCURL`
else
echo "Downloading MPC for GCC.. :)"
wget -c $MPCURL
sleep 3s
echo "Extracting the compressed file!"
tar xvf `basename $MPCURL`
fi 

# Moving these to the gcc.

mv -v `basename $GMPURL .tar.lz` `basename $GCCURL .tar.gz `/gmp 
mv -v `basename $MPFRURL .tar.xz` `basename $GCCURL .tar.gz `/mpfr  
mv -v `basename $MPCURL .tar.gz` `basename $GCCURL .tar.gz`/mpc 




# Installing part.
cd /usr/local/src/build-binutils
/usr/local/src/`basename $BINUTILSURL .tar.gz`/configure --target=${TARGET} --prefix=${PREFIX} --with-sysroot --disable-nls --disable-werror
make -j2 all
make -j2 install
echo "Done installing binutils."

cd /usr/local/src/build-gcc/
export PATH=$PATH:$PREFIX/bin
/usr/local/src/`basename $GCCURL .tar.gz`/configure --target=${TARGET} --prefix=${PREFIX} --disable-nls --enable-languages=c,c++ --without-headers
make -j2 all-gcc
make -j2 all-target-libgcc
make -j2 install-gcc
make -j2 install-target-libgcc
echo "Done installing gcc."


echo "Your environment should now have a working i686-elf cross compiler tool chain!"
echo 'But first, you need to do this:'
echo '	export PATH=$PATH:/usr/local/cross/bin'
echo " "
echo "Also make sure you have a working nasm assembler."
