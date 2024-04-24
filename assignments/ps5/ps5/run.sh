#!/bin/bash

# Run executables with corresponding arguments

# Define the number of times quicksort will be run
SAMPLE_SIZE=10

# Loop over all executables in the build folder
for executable in ./build/*; do
		# Get the name of the executable without the path
		executable_name=$(basename "$executable")

		# Run the executable with the corresponding arguments
		./"$executable" "$executable" "$SAMPLE_SIZE" >> ./tests/optimization_times.txt
done
