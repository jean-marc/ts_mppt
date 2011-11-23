set datafile separator ","
set timefmt "%b %d %H:%M:%S"
set title 'Charge'
set xdata time
set xlabel "time"
#set xrange["27-Oct-08:00:00":"27-Oct-22:00:00"]
set ylabel "Voltage (V)"
set y2label "Power (W)"
set ytics nomirror
set y2tics
set grid x y
set yrange[24:35]
set y2range[50:200]
plot '/var/log/ts_mppt.log' every 5 using 1:21 axes x1y2 with lines lt 4 title '','/var/log/ts_mppt.log' every 5 using 1:2 title 'battery' with lines,'/var/log/ts_mppt.log' every 5 using 1:5 title 'array' with lines
