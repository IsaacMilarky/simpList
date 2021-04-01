#!/bin/bash
mkdir build
cd build
cmake .. && make
sudo cp SimpList /usr/local/bin
#Set up cron job
sudo touch /etc/cron.allow
sudo echo "root" >> /etc/cron.allow
sudo touch /var/spool/cron/root
sudo /usr/bin/crontab /var/spool/cron/root
#Check deadlines every five minutes
echo "*/5  * * * * notify-send | SimpList update" >> /var/spool/cron/root

