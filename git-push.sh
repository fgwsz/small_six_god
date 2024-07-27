#!/bin/sh
echo "You Can Input q For Abort."
read -p "Input Git Commit Info: " commit_info
if [ "$commit_info" != "q" ]; then
    git add ./source/*
    git add ./CMakeLists.txt
    git add ./*.sh
    git add ./*.py
    git add ./LICENSE
    git add ./README.md
    git add ./.gitignore
    git commit -m "$commit_info"
    git push
fi
