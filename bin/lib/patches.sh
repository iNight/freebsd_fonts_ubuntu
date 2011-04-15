patches() {
  patch_dir=$1
  mkdir files
  for _f in $(cat ${patch_dir}/series) ; do
    echo "${patch_dir}/$_f"
    (cd files && splitdiff -ad ../${patch_dir}/$_f)
  done
}
