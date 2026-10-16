#!/bin/bash
set -e

make clean
make

for size in 128 256 512 1024; do
  for run in 1 2 3 4 5; do
    echo "Dataset: $size — Run: $run"
    /usr/bin/time -v ./pearson \
      "data/${size}.data" \
      "data_o/${size}_seq.data"
  done
done