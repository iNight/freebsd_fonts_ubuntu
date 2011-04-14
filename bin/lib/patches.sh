patches() {
  mkdir files
  for _f in $(cat debian/patches/series) ; do
    echo "debian/patches/$_f"
    (cd files && splitdiff -ad ../debian/patches/$_f)
  done
}
