rename() {
  rename_regexp=$1
  for _f in $(ls files) ; do
    echo -n "Path file $_f -> "
    name=`echo -n $_f | sed $rename_regexp`
    mv files/$_f files/$name
    echo "$name"
  done
}
