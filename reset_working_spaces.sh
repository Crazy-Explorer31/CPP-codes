#!/bin/bash

for i in 1 2 3 4 5 6 7:
do
echo "work_space_${i}.cpp"
cat "work_space_0.cpp" > "work_space_${i}.cpp"
done