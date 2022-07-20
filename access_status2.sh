#!/bin/bash
PV=$(cat /var/log/nginx/access.log | sed -n /`date "+%d\/%b\/%Y"`/p | awk '{print $1}' | sort |wc -l)
UV=$(cat /var/log/nginx/access.log| sed -n /`date "+%d\/%b\/%Y"`/p |awk '{print $1}' |sort|uniq -c |wc -l)
#DOWNLOADS=$(cat /var/log/nginx/access.log | grep /download/xswitch-install.tar.gz | grep `date "+%d/%b/%Y"` | wc -l)
DOWNLOADS=$(cat /var/log/nginx/access.log|grep /download/xswitch-install.tar.gz|sed -n /`date "+%d\/%b\/%Y"`/p |awk '{print $1}' |sort|uniq -c |wc -l)
DATE=$(date +"%Y-%m-%d")
sql="INSERT INTO statistics2 (pv, uv, downloads, day) VALUES ($PV, $UV, $DOWNLOADS, '$DATE');"
echo $PV $UV $DOWNLOADS $DATE $sql
psql -U nginx nginx -c "$sql"
