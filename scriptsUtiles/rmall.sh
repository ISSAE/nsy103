
git filter-branch --force --index-filter "git rm -r --cached --ignore-unmatch $1" --prune-empty --tag-name-filter cat -- --all
git reflog expire --expire=now --all
git gc --prune=now
git gc --aggressive --prune=now
