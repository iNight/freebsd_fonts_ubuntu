get() {
  url=$1; name=$2; extension=$3; md5=$4

  echo -n "Fetching $name -> "
  wget -q $url
  echo "done"

  new_md5=$(md5 -q $name)

  echo -n "MD5 for $name -> "
  if [ $new_md5 = $md5 ]; then
     echo " ok"
  else
    echo "bad"
    exit EXIT_CODE
  fi

  echo -n "Extracting $name -> "
  case $extension in
    .tar.gz)  tar xzf $name;;
    .tar.bz2) tar xjf $name;;
    .gz)      gunzip -c $name | patch -sp1;;
  esac
  echo "finish."
  rm $name
}
