#!/bin/sh

EXIT_CODE=2

usage() {
  echo "usage: `basename $0` cairo|fontconfig"
}

if [ $# -ne 1 ]; then
  usage
  exit $EXIT_CODE
else
  port=$1
fi

case $port in
  cairo)
    pkgver=1.10.2-2ubuntu2
    extension=.tar.gz
    name=cairo_${pkgver}.debian${extension}
    url=http://archive.ubuntu.com/ubuntu/pool/main/c/cairo/${name}
    dir=debian/patches
    rename='s/cairo[-_][1.10.0_]*/patch-/'
    md5=c28ce4e75bf13c2a10727b2af1385059
    ;;
  fontconfig)
    pkgver=2.8.0
    pkgver2=2ubuntu1.diff
    extension=.gz
    name=fontconfig_${pkgver}-${pkgver2}${extension}
    url=http://archive.ubuntu.com/ubuntu/pool/main/f/fontconfig/$name
    dir=debian/patches
    rename='s/fontconfig[-_][^_]*_/patch-/'
    md5=ea8666fd1906bf101b9cfc42bf325f94
    ;;
  freetype2)
    pkgver=2.4.2-2.1
    extension=.gz
    name=freetype_${pkgver}.diff.gz
    url=https://launchpad.net/ubuntu/natty/+source/freetype/${pkgver}/+files/$name
    dir=debian/patches-freetype
    rename='s/fontconfig[-_][^_]*_/patch-/'
    md5=68a5fe548b573eb994d212b0928f249b
    ;;
  libxft)
    pkgver=2.1.14
    pkgver2=2ubuntu1.diff
    extension=.gz
    name=xft_${pkgver}-${pkgver2}${extension}
    url=http://archive.ubuntu.com/ubuntu/pool/main/x/xft/$name
    dir=debian/patches
    rename_regexp='s/fontconfig[-_][^_]*_/patch-/'
    md5=b965b9575673ebed2a86992b4096731d
    ;;
esac


. lib/get.sh
. lib/patches.sh
. lib/rename.sh

#get $url $name $extension $md5
#patches $dir
#rename $regexp
#clean_up
