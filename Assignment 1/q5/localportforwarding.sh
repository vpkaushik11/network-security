#!/bin/bash

# Define your SSH server details
REMOTE_SERVER="your_remote_server.com"
USERNAME="your_ssh_username"

# Define the local port to listen on and the destination host/port
LOCAL_PORT=8080
DESTINATION_HOST="destination_host.com"
DESTINATION_PORT=80

# Establish local port forwarding using SSH
ssh -L $LOCAL_PORT:$DESTINATION_HOST:$DESTINATION_PORT $USERNAME@$REMOTE_SERVER
