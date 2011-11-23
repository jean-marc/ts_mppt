#!/bin/bash
echo "Content-type: image/svg+xml"
echo
gnuplot svg.gnu plot.gnu
