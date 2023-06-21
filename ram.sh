#!/bin/bash

TOTAL_RAM=$(free -mh --si | awk  {'print $2'} | head -n 2 | tail -1)
USED_RAM=$(free -mh --si | awk  {'print $3'} | head -n 2 | tail -1)
MB='MB'

printf "$USED_RAM/$TOTAL_RAM"
