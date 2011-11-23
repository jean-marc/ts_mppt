#!/bin/bash
echo "Content-type: image/png"
echo
gnuplot png.gnu plot.gnu
