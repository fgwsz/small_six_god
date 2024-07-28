#!/bin/bash
root_path=$(dirname "$(readlink -f "$0")")
build_path="$root_path/build/linux"
if [ -d "$build_path" ]; then
    rm -rf "$build_path"
fi
