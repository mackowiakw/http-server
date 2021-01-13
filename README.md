# http-server
- Simple HTTP server for Linux written in modern C++

- Olny text files are operated. **Content-Type** header is attached only to text files, so browsers cannot read images properly

- It's runnig on localhost (fits for my purpose), but is is possible to easy extend its working area

- Served files are placed in `server/SERVER_ROOT_FOLDER` (you can change this in config.hpp)

- It's mostly corresponig with [RFC 2616](https://tools.ietf.org/html/rfc2616)

Check also my .NET [http-client](https://github.com/mackowiakw/http-client) with GUI

### Usage:

Clone this repository:

```
git clone https://github.com/mackowiakw/http-server.git

cd http-server
```

### Preffered way - VS Code:

Only if you're using Windows and you have WSL installed:

```
wsl
```

Otherwise skip this command and continue in Linux shell. Then open in VS Code:

```
code .
```

And just hit **F5**. Server is now available at: http://localhost:1234


### You can also compile it manually:

```
g++ server/main.cpp -o bin/server.out -Wall -lpthread -std=c++17
```

Start with:

```
./bin/server.out
```
