# http-server
Simple HTTP server for Linux written in C++

<!-- Client for Windows written in C# -->
### Usage:

Clone this repository:

```
git clone https://github.com/mackowiakw/http-server.git

cd http-server
```

### Server (Fastest way - VS Code):

Only if you're using Windows and you have WSL installed:

```
wsl
```

Otherwise skip this command and continue in Linux shell. Then open in VS Code:

```
code .
```

And just hit **F5**. Server is now available at: http://localhost:1234



### You can compile it also manually:

```
g++ server/main.cpp -o bin/server.out -Wall -lpthread -std=c++17

./bin/server.out
```



### Windows client (with hardcoded request URL XD):

```
gcc client/client.c -o bin/client.exe -Wall -lwsock32

./bin/client.exe
```
