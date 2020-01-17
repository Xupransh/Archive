#!/bin/bash
start=$SECONDS 
counter=0
while true; do
  r1=$((RANDOM%50+1))
  r2=$((RANDOM%51))
  r3=$((RANDOM%51))
  r4=$((RANDOM%51))
  widthMin=$((r1+r2+r3+r4+3))

  if ((RANDOM%100==0)); then
    widthMin=1 #test too small widths, but not too often
  fi
  if (($widthMin > 50)); then
    continue
  fi
  width=$((RANDOM%(51-widthMin)+widthMin))
  arg="$r1 $r2 $r3 $r4 $width"

  mine="$(./onerow $arg)"
  if [[ "$counter" -gt 5000 ]]; then
       echo "Counter limit reached, exit script."
       duration=$(( SECONDS - start ))
       echo "$duration"
       exit 0
  fi
  counter=$(( counter +1 ))
done
