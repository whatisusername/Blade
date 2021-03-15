#!/bin/bash

filename=$1

while read FILE; do
	if [ -f "$FILE" ] || [ -d "$FILE" ]; then
		echo "Delete $FILE"
		rm -r $FILE
	else
		echo "$FILE does not exist."
	fi
done < $filename
