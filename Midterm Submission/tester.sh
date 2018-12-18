#!/bin/bash

tests="$PWD/tests/puzzles/*.puz"
solutions="$PWD/tests/solutions/*.step"

for f in $tests
do
	echo $f
  ./burster "$f"
done



