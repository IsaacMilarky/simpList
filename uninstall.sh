#!/bin/bash
sudo rm /usr/local/bin/SimpList
rm build/*
crontab -u root -l | grep -v 'notify-send | SimpList update' | crontab -u root
