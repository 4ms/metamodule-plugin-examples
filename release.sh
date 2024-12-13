echo "Usage:"
echo "    release.sh PluginName Version"
echo "    release.sh Bogaudio v1.2.3"
git tag -a $2 -m "$1-$2"
git push origin $2
gh workflow run build_release.yml -f plugin="$1" -f do_release=true -r $2
