#!/bin/bash

# Prompt the user for input values
echo "Enter the basic salary:"
read basics

echo "Enter the travel allowance (TA):"
read ta

# Calculate 10% of basic salary
percent_of_basics=$(echo "$basics * 0.10" | bc)

# Calculate the gross salary
gross_salary=$(echo "$basics + $ta + $percent_of_basics" | bc)

# Print the gross salary
echo "The gross salary is: $gross_salary"
