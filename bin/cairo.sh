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
    # cairo 
    origin_pkgver=1.10.2
    origin_extension=.tar.gz
    origin_name=cairo-${origin_pkgver}${origin_extension}
    origin_url=http://cairographics.org/releases/$origin_name
    origin_md5=f101a9e88b783337b20b2e26dfd26d5f
    # patch
    patch_pkgver=1.10.2-2ubuntu2
    patch_extension=.tar.gz
    patch_name=cairo_${patch_pkgver}.debian${patch_extension}
    patch_url=http://archive.ubuntu.com/ubuntu/pool/main/c/cairo/${patch_name}
    patch_dir=debian/patches
    patch_rename='s/cairo[-_][1.10.0_]*/patch-/'
    patch_md5=c28ce4e75bf13c2a10727b2af1385059
    ;;
  fontconfig)
    # patch
    origin_pkgver=2.8.0
    origin_extension=.tar.gz
    origin_name=fontconfig_${origin_pkgver}.orig${origin_extension}
    origin_url=http://archive.ubuntu.com/ubuntu/pool/main/f/fontconfig/$origin_name
    origin_md5=77e15a92006ddc2adbb06f840d591c0e
    # patch
    patch_pkgver=$origin_pkgver
    patch_pkgver2=2ubuntu1.diff
    patch_extension=.gz
    patch_name=fontconfig_${patch_pkgver}-${patch_pkgver2}${patch_extension}
    patch_url=http://archive.ubuntu.com/ubuntu/pool/main/f/fontconfig/$patch_name
    patch_dir=debian/patches
    patch_rename='s/fontconfig[-_][^_]*_/patch-/'
    patch_md5=ea8666fd1906bf101b9cfc42bf325f94
    ;;
  freetype2)
    # patch
    origin_pkgver=2.4.4
    origin_extension=.tar.bz2
    origin_name=freetype-${origin_pkgver}${origin_extension}
    origin_url=http://downloads.sourceforge.net/sourceforge/freetype/$origin_name
    origin_md5=b3e2b6e2f1c3e0dffa1fd2a0f848b671
    # patch
    patch_pkgver=2.4.2-2.1
    patch_extension=.gz
    patch_name=freetype_${patch_pkgver}.diff.gz
    patch_url=https://launchpad.net/ubuntu/natty/+source/freetype/${patch_pkgver}/+files/$patch_name
    patch_dir=debian/patches-freetype
    patch_rename='s/fontconfig[-_][^_]*_/patch-/'
    patch_md5=68a5fe548b573eb994d212b0928f249b
    ;;
esac


. lib/get.sh
. lib/patches.sh
. lib/rename.sh

#get $origin_url $origin_name $origin_extension $origin_md5
#get $patch_url $patch_name $patch_extension $patch_md5
patches $patch_dir
#rename $patch_rename
#clean_up
