cmd="git filter-branch --force --index-filter 'git rm -rf --cached --ignore-unmatch $1' --prune-empty --tag-name-filter cat -- --all"

echo $cmd
