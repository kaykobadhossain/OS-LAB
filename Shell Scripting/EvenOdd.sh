echo "Even Or Odd Programme"
echo "Enter the Number"
read number
if [ $((number % 2)) -eq 0 ]; then
    echo "$number is Even"
else
    echo "$number is Odd"
fi