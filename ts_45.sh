#!/bin/bash
# monitoring also take place here, if the voltage goes below threshold we should shutdown
# timing is important, the relay-driver needs to be set-up so as to give enough time
# for the server to shutdown clients and itself
# a bit convoluted because lack of float support in bash
TS_45=/usr/local/bin/ts_45
LOG=/var/log/ts_45.log
# this is what the log file will look like, if more entries are needed the ts_45.c program will
# have to be modified
#	May 16 12:25:01,25.16,0.00,25.17
#	May 16 12:30:01,24.97,0.00,25.02
#	May 16 12:35:01,24.82,0.00,24.82
SCRIPT=/usr/local/bin/ts_mppt.awk
# should be above the value set in the relay driver
LOW_VOLTAGE_DISCONNECT=24.5;
CURRENT_VOLTAGE=$($TS_45 | gawk -f $SCRIPT | tee -a $LOG | gawk -F, '{ print $2 }')
if [ $(echo "$CURRENT_VOLTAGE < $LOW_VOLTAGE_DISCONNECT" | bc -q) -eq 1 ]
then 
	/sbin/poweroff
fi
exit
