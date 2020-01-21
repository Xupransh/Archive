#!/bin/bash

while :; do
  rn=$((RANDOM*RANDOM))
  ./genreq graph requests_auto 10 $rn 1000000 1000000 1500000 1500000 1000 10000
  ./mp10-gold graph requests_auto 0 > goldout.txt
  mv result.c result.gold.c
  ./mp10 graph requests_auto 0 > out.txt
  diff="$(diff goldout.txt out.txt)"
  if [[ "$diff" == "" ]]; then
    printf "PASS - "
  else
    printf "Test failed! $rn"
    break
  fi
  diff="$(diff result.gold.c result.c)"
  if [[ "$diff" == "" ]]; then
    printf "PASS - $rn\n"
  else
    printf "Image failed! $rn\n"
    printf $diff
    break
  fi
  if [[ "$1" == "once" ]]; then
    break
  fi
done
