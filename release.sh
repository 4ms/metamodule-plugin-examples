if [ "$#" -ne 2 ]; then
	echo "Usage:"
	echo "To release one plugin:"
	echo "    release.sh PluginName vX.Y.Z"
	echo ""
	echo "To release all plugins"
	echo "    release.sh all vX.Y.Z"
	exit
fi

if [ ! -d "$1" ] && [[ "$1" != "all" ]]; then
	echo "Must specify a plugin name (root-level dir name) or 'all'"
	exit
fi

# Check valid version
rx='^v([0-9]+\.){2,2}(\*|[0-9]+)(\-.*){0,1}$'
if [[ $2 =~ $rx ]]; then
	if [ "$1" == "all" ]; then
		git tag -a $2 -m "$2"
		git push origin $2
		gh workflow run build_release.yml -f plugin="./" -f do_release=true -r $2
	else
		git tag -a $1-$2 -m "$1-$2"
		git push origin $1-$2
		gh workflow run build_release.yml -f plugin="$1" -f do_release=true -r $1-$2
	fi
else
	echo "Error: Version must be in the form 'vX.Y.Z' or 'vX.Y.Z-*'"
	echo "Where X, Y, and Z are one or more digits 0-9, and * is any string"
fi

