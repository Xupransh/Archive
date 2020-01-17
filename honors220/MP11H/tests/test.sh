#!/bin/bash

# Place this fine in your .../MP11H/tests folder ONLY
# make sure you cd into .../MP11H/tests BEFORE running with ./run_tests.sh
# If you are not able to execute, run 'chmod +x ./run_tests.sh' first
# Although there are no destructive commands in this script, I am not
# responsible for any unforeseen side-effects this script may induce.

# Acknowledgements:
# 1. This should not replace your traditional bug testing by hand.
# 2. This script will most likely hang on massively interactive programs
#    such as testprog.c. You may quit at any time using ^Z or ^C

# Know script side-effects:
# 1. Compiles your most recent mp11.c code to c220
# 2. Creates .../MP11H/tests/testing_result.txt,
#            .../MP11H/tests/testing_result_gold.txt
#            .../MP11H/tests/testing_out.asm && .obj
#            .../MP11H/tests/testing_out_gold.asm && .obj
# 3. Loads the lc3sim executibles into your bash $PATH variable using 'module load lc3tools'

# Check for the lc3tools module
if [[ $(module list | grep "lc3tools") ]]; then
  echo "lc3tools module already loaded."
else
  echo "Loading lc3tools module"
  eval "module load lc3tools 2>&1 >/dev/null"
fi
# Loop over all *.c files in the directory
for testfile in ./*.c; do
  echo " "
  # Navigate to executable working directory
  pushd ../ 2>&1 >/dev/null
  echo "Now testing $testfile..."
  # Compile your most recent edits
  eval "make 2>&1 >/dev/null"
  # Run and output assembly for gold and your code, the turn into binary
  eval "./c220 < ./tests/${testfile##*/} > ./tests/testing_out.asm"
  eval "lc3as ./tests/testing_out 2>&1 >/dev/null"
  eval "./c220-gold < ./tests/${testfile##*/} > ./tests/testing_out_gold.asm"
  eval "lc3as ./tests/testing_out_gold 2>&1 >/dev/null"

  # Generate random numbers to press in testing script:
  sleepDuration="0.1"
  rand1="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand2="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand3="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand4="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand5="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand6="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand7="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand8="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand9="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand10="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand11="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand12="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand13="sleep $sleepDuration; echo $((1 + RANDOM % 10));"
  rand14="sleep $sleepDuration; echo $((1 + RANDOM % 10));"

  # Run LC3Sim on your code and compare with gold output.
  eval "{ sleep 0.5; echo "c"; $rand1 $rand2 $rand3 $rand4 $rand5 $rand6 $rand7 $rand8 $rand9 $rand10 $rand11 $rand13 $rand14 } | lc3sim ./tests/testing_out > ./tests/testing_result.txt"
  eval "{ sleep 0.5; echo "c"; $rand1 $rand2 $rand3 $rand4 $rand5 $rand6 $rand7 $rand8 $rand9 $rand10 $rand11 $rand13 $rand14 } | lc3sim ./tests/testing_out_gold > ./tests/testing_result_gold.txt"
  # Print differences to stdout
  echo "Differences in $testfile:"
  eval "diff <(nl ./tests/testing_result.txt -v 33 | grep -v "R0" | grep -v "PC" | grep -v "TRAP") <(nl ./tests/testing_result_gold.txt -v 33 | grep -v "R0" | grep -v "PC" | grep -v "TRAP")"

  # Return to working directory and separate from following outputs.
  popd 2>&1 >/dev/null
  echo " "
  echo " "
done
