#!/bin/bash

source '/usr/lib/smartlog/smartlog.sh'

TYPEOUT=true
tip "Welcome to my script"
TYPEOUT=false


log "Doing stuff successfully"
# stuff
ok

log "Doing stuff unsuccessfully"
# stuff
fail


warn "I'm about to stop"

die "I'm stopping now"
