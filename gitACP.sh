#!/bin/bash

wrkPath="."

git pull
git add $wrkPath -A
git commit -m "updates - scripted"
git push
git status

exit 0
