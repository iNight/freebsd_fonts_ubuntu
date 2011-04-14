rename() {
  for _f in $(ls files) ; do
    echo -n "Path file $_f -> "
    name=`echo -n $_f | sed 's/cairo[-_][1.10.0_]*/patch-/'`
    mv files/$_f files/$name
    echo "$name"
  done
}
