#!/bin/bash
PV=$(cat /var/log/nginx/access.log | sed -n /`date "+%d\/%b\/%Y"`/p | awk '{print $1}' | sort |wc -l)
UV=$(cat /var/log/nginx/access.log| sed -n /`date "+%d\/%b\/%Y"`/p |awk '{print $1}' |sort|uniq -c |wc -l)
DOWNLOADS=$(cat /var/log/nginx/access.log|grep /download/xswitch-install.tar.gz|sed -n /`date "+%d\/%b\/%Y"`/p |awk '{print $1}' |sort|uniq -c |wc -l)
DATE=$(date +"%Y-%m-%d")
sql="INSERT INTO DAILY (PV, UV, DOWNLOADS, DATE) VALUES (\"$PV\", \"$UV\", \"$DOWNLOADS\", \"$DATE\");"
echo $PV $UV $DOWNLOADS $DATE $sql
sqlite3 data.db "$sql"
