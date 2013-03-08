#!/usr/bin/python
# polls the battery controler to monitor charge, voltage and shutdown computers when threshold is reached

import serial
import time
import os
import sys
ser=serial.Serial('/dev/ts_45',9600,timeout=1)
#reads historical data to extract some information
ser.write('!')
out=ser.readline();
fullcurr=int(out.split()[2],16) #cx40 40 amps
volt_disconnect=14.9 #11.7
set=out.split()[13]
#sys.stderr.write(out)
#starts polling the controler
#while (1):
ser.write(' ')
out=ser.readline()
#sys.stderr.write(out)
v=(float(out.split()[3])*.032)+9		
#os.system('logger battery voltage '+str(v)+'V');
#if(v<volt_disconnect): 
#	os.system('logger -s battery voltage below '+str(volt_disconnect)+'V');
#	os.system('halt');			
print "voltage ",v,"V"		
print "end_charge_voltage ",(float(out.split()[4])*.032)+9,"V"		
print "state_of_charge ",100*float(out.split()[1])/30,"%"
print "load_current ",(float(out.split()[6])/fullcurr)*40,"A"
print "internal_temperature ",25+(float(out.split()[12])),"C"
print "external_temperature ",25+(float(out.split()[13])),"C"
print "PV_current ",(float(out.split()[14])/fullcurr)*40,"A"
#time.sleep(0)
#break 
