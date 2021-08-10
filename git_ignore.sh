#!/bin/sh
git ls-files -oi --exclude-standard
find . -name .DS_Store -print0 | xargs -0 git rm -f --ignore-unmatch
find . -name *.o -print0 | xargs -0 git rm -f --ignore-unmatch
find . -name *.out -print0 | xargs -0 git rm -f --ignore-unmatch
