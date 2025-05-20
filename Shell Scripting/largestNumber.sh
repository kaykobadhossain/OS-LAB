echo "Largest Number Programme"
#echo "Enter number count"
#read count
count=5
echo "Enter $count numbers"
for ((i=0; i<count; i++)); do
    read number[$i]
done
largest=${number[0]}
for ((i=1; i<count; i++)); do
    if [ ${number[i]} -gt $largest ]; then
        largest=${number[$i]}
    fi
done
echo "Largest number is: $largest"