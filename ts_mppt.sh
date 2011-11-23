#!/bin/bash
/usr/local/bin/ts_mppt | gawk -f /usr/local/bin/ts_mppt.awk >> /var/log/ts_mppt.log
