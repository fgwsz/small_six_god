#!/bin/sh
read -p "Input Git Repo Name: " repo_name
echo "# $repo_name" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin "git@github.com:fgwsz/$repo_name.git"
git push -u origin main
