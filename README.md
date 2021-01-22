# http-server
- Simple HTTP server for Linux written in modern C++

- Text, image, audio, video and pdf files are operated. In these cases proper *Content-Type* header is attached to the response.

- It's runnig on localhost (fits for my purpose), but is is possible to easily extend its working area

- Served files are placed in `SERVER_ROOT_FOLDER` (you can change this in include/config.hpp)

- It's mostly corresponding with [RFC 2616](https://tools.ietf.org/html/rfc2616)

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

And just hit **F5**. Server is now available at: http://localhost:8080


### You can also compile it manually:

```
g++ src/*.cpp -Iinclude -lpthread -std=c++17 -Wall -o bin/main
```

Start with:

```
./bin/main
```
