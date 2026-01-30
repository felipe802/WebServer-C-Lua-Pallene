#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
    // Load our finance script
    if(luaL_dofile(L, "finance.lua") != LUA_OK) {
        printf("Error: %s\n", lua_tostring(L, -1)); // Problem to open the file
        return 1;
    }

    // Prepare to call the 'calculate_yield' function
    lua_getglobal(L, "calculate_yield");
    lua_pushnumber(L, 35.50); // Fake price for a while
    lua_pushnumber(L, 2.2); // Fake dividend for now
    
    // Call function: 2 args, 1 result
    if(lua_pcall(L, 2, 1, 0) != LUA_OK) {
        printf("Error running function: %s\n", lua_tostring(L, -1));
    }

    double result = lua_tonumber(L, -1);
    printf("C: BBAS3 estimated yield: %.2f\n", result);

    lua_close(L);
    return 0;
}