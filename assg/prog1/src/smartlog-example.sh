#!/bin/bash

set +e # set this to avoid stopping on error
source '/usr/lib/smartlog/smartlog.sh'


# Greeting
TYPEOUT=true
tip "Welcome to my script"
TYPEOUT=false



# 2> /dev/null suppresses error from the command
log "Doing stuff successfully"
if ls 2> /dev/null > /dev/null
then
  ok
else
  fail
fi

log "Doing stuff unsuccessfully"
if cat /dev/sda 2> /dev/null > /dev/null
then
  ok
else
  fail
fi

# Execution
s_exn "Executing ls" "ls"


# Checks
prompt "Filename"
if check_var "reply" "$REPLY"
then
  if check_file "given" "$REPLY"
  then
    tip "I see you passed in an existing filename as an argument"
  else
    warn "The given input is not an existing file"
  fi
else
  warn "The reply was empty"
fi


# Prompts
if yesno "Do you want to stop"
then
  tip "That's great"
else
  warn "That's too bad, I'm going to stop anyway"
fi


die "I'm stopping now"
