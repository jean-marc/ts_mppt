#!/bin/bash
echo "Content-type: application/pdf"
echo
gnuplot pdf.gnu plot.gnu | ps2pdf - -
