#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main() {
    lua_State *L = luaL_newstate();
    // Each lua_state is a thread
    luaL_openlibs(L);
    
    // Load our finance script
    if(luaL_dofile(L, "finance.lua") != LUA_OK) { // Check the Lua file
        printf("Error: %s\n", lua_tostring(L, -1)); 
        return 1;
    }

    // Prepare to call the 'calculate_yield' function
    lua_getglobal(L, "calc_indicators");
    lua_pushnumber(L, 35.50); // Fake price for a while
    lua_pushnumber(L, 2.2); // Fake dividend for now
    
    // Call function: passing 2 args and expecting 2 values, 0 is default
    if(lua_pcall(L, 2, 2, 0) != LUA_OK) { // Return 2 values, -1 and -2 from the stack
        printf("Error running function: %s\n", lua_tostring(L, -1)); // The top error message
    } 

    double ceiling = lua_tonumber(L, -1); // On the top
    double yield = lua_tonumber(L, -2); // On the base
    printf("BBAS3 Analysis----------------\n");
    printf("Current Yield: %.2f\n", yield);
    printf("Price Ceiliing: R$ %.2f\n", ceiling);

    lua_close(L);
    return 0;
}