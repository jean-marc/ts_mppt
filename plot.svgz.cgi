#!/bin/bash
echo "Content-type: image/svg+xml"
echo "Content-Encoding: gzip"
echo
gnuplot svg.gnu plot.gnu | gzip -
