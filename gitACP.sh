#!/bin/bash
# for cs340-finalProject
# set working directory & username

uName=$(whoami)
if [ $UID -eq 0 ]; then
    # exit if root
    echo "error: this should not be run with elevated permissions" >&2
    exit 1
fi
# wrkPath="/home/$uName/code/GitHub/cs340-finalProject"

# add & commit current changes
git add .. -A
git commit -m "updates - scripted"

# pull changes, merge, & push
git pull
git add .. -A
git commit -m "merge - scripted"
git push
git status

exit 0
