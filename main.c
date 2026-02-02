#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define PORT 8080

void send_response(int client_socket, lua_State *L) {
    lua_getglobal(L, "calc_indicators");
    lua_pushnumber(L, 35.50); 
    lua_pushnumber(L, 2.2); 
    
    if(lua_pcall(L, 2, 1, 0) != LUA_OK) { // Now, only return the big html from finance.lua
        const char *err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        char error_resp[512];
        sprintf(error_resp, "HTTP/1.1 500 Internal Server error\n\n %s", err);
        send(client_socket, error_resp, strlen(error_resp), 0); // The top (stack) error message
    }
    else {
        const char *html = lua_tostring(L, -1);
        char response[4096];
        // Standard HTTP Header so the browser understands it's a webpage
        int len = snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s", strlen(html), html);

        send(client_socket, response, len, 0);
    }
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 1. Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 2. Bind and listen
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Method Engine Online at http://localhost:%d\n", PORT);

    // 3. The server Loop
    while(1) {
        client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        if (luaL_dofile(L, "finance.lua") != LUA_OK) {
            printf("Thread error: %s\n", lua_tostring(L, -1));
            lua_close(L);
            close(client_sock);
            continue;
        }

        send_response(client_sock, L);

        lua_close(L);
        close(client_sock);
    }
    return 0;
}
