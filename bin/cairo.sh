#!/bin/sh

EXIT_CODE=2

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
patch_md5=c28ce4e75bf13c2a10727b2af1385059

. lib/get.sh
. lib/patches.sh
. lib/rename.sh

#get $origin_url $origin_name $origin_extension $origin_md5
#get $patch_url $patch_name $patch_extension $patch_md5
#patches
#rename 
#clean_up
