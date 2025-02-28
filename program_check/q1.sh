#!/bin/sh
# Prompt user to enter file path
echo "Enter integer:"
read integer
sum=0;

while [ $integer -gr 0 ]; do
remainder=$( $integer % 10 | bc)

sum=(($sum + $remainder))



