#!/bin/sh
echo "You Can Input q For Abort."
read -p "Input Git Commit Info: " commit_info
if [ "$commit_info" != "q" ]; then
    git add ./source/*
    git add ./CMakeLists.txt
    git add ./build.sh
    git add ./clean.sh
    git add ./LICENSE
    git add ./README.md
    git add ./.gitignore
    git add ./git-init.sh
    git add ./git-push.sh
    git commit -m "$commit_info"
    git push
fi
