#!/bin/bash

for i in 0 1 2 3 
do
   echo "Testing with prueba$i.txt"
   ./student_source/my_route_lookup linearSearch/routing_table.txt linearSearch/prueba$i.txt > diffs/my$i.txt
   ./linearSearch/linearSearch linearSearch/routing_table.txt linearSearch/prueba$i.txt > diffs/linear$i.txt
done
echo "Finished. Output files in diffs/"
