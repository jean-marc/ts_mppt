#!/bin/bash
#could we do the logging from crontab?
/usr/local/bin/ts_45 | gawk -f /usr/local/bin/ts_mppt.awk >> /var/log/ts_45.log
/usr/local/bin/ts_mppt_45 | gawk -f /usr/local/bin/ts_mppt.awk >> /var/log/ts_mppt_45.log
