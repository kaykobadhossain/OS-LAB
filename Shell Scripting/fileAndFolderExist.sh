echo "Enter file name:"
read filename

if [ -f "$filename" ]; then
    echo "File exist"
else
    echo "File not exist"
fi

cd .. #move back cause folder is in parent directory
# Check if the folder exists
folder="Shell Scripting"
if [ -d "$folder" ]; then
    echo "$folder is here"
#     cd "$folder"
#     echo "current Directory: $(pwd)"
else
    echo "$folder foleder not found"

fi