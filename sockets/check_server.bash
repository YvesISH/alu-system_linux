#!/bin/bash

# Start the server in the background
./todo_api_3 &
SERVER_PID=$!
sleep 1  # Give the server a second to start

# Send the requests
curl -d "holberton=school" -X POST http://localhost:8080/
curl -d "holberton=school&street=972_Mission" -X POST http://localhost:8080/test
curl -d "holberton=school&street=972_Mission&city=San_Francisco&zip=94103" -X POST http://localhost:8080/test/test

# Kill the server
kill $SERVER_PID

