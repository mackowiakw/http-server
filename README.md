# http-server
Simple HTTP server

## Compilation

Server (Linux):
`g++ server/main.cpp -o bin/server.out -Wall -lpthread -std=c++17`

Client (Windows):
`gcc client/client.c -o bin/client.exe -Wall -lwsock32`

## Usage

Server:
`./bin/server.out`

Client:
`./bin/client.exe`
