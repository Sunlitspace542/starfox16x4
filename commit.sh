echo "Enter commit description:"
read desc
git add . && git commit -m "$desc" && git push -u origin master
