#!/bin/bash

compare1=$1
compare2=$2
filename=$3

base=$(dirname "$0")
output=$base/Output/
echo "output path is $output"

mkdir -p $output

echo "Comparing..."
diff -r $compare1 $compare2 > $output/$filename

echo "Start replace text in file..."

# Remove "Only in "
sed -i 's/Only in //g' $output/$filename

# Replace ": " with "/"
# e.g. "Animations: Ability_Combo_01_Fast.uasset" -> "Animations/Ability_Combo_01_Fast.uasset"
sed -i 's/: /\//g' $output/$filename

echo "Done!"
