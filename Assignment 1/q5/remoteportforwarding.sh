#!/bin/bash

# Define your SSH server details
REMOTE_SERVER="your_remote_server.com"
USERNAME="your_ssh_username"

# Define the remote port to listen on and the local host/port
REMOTE_PORT=2222
LOCAL_HOST="localhost"
LOCAL_PORT=22

# Establish remote port forwarding using SSH
ssh -R $REMOTE_PORT:$LOCAL_HOST:$LOCAL_PORT $USERNAME@$REMOTE_SERVER
