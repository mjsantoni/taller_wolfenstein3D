// Lua está pensado para trabajar con C, por lo cuál
// la biblioteca nos pide que nuestras funciones sean compatibles
// con la C, desactivando el name mangling
#ifdef __cplusplus
  // Este header es básicamente una inclusión de los 3 de abajo
  // pero protegido con extern "C"
  #include <lua5.3/lua.hpp>
#else
  #include <lua5.3/lua.h>
  #include <lua5.3/lualib.h>
  #include <lua5.3/lauxlib.h>
#endif

#include <iostream>

bool CheckLua(lua_State *L, int r) {
    if (r == LUA_OK) return true;
    std::string errormsg = lua_tostring(L, -1);
    std::cout << errormsg << std::endl;
    return false;
}

int main(int argc, char* argv[]) {

    // Create Lua State
    lua_State* L = luaL_newstate();

    // Add standard libraries to Lua Virtual Machine
    luaL_openlibs(L);

    // Register our C++ Function in the global Lua space
    //lua_register(L, "HostFunction", lua_HostFunction);

    // Load File
    if(!CheckLua(L, luaL_dofile(L, "../lua_test/test.lua"))) return 1;


    // Stage 3: Call Lua Function
    std::cout << "[CPP] Get addToMap\n";
    lua_getglobal(L, "addToMap");

    if (!lua_isfunction(L, -1)) {
        std::cout << "No function exists\n";
        return -1;
    }

    lua_pushnumber(L, 47);
    lua_pushstring(L, "chain_gun");
    lua_pushnumber(L, 100);
    lua_pushnumber(L, 160);

    std::cout << "[CPP] Calling 'addToMap'\n";
    // Lua pcall recibe: L, cant argumentos de la funcion, cant cosas que devuelve, how to handle error
    lua_pcall(L, 4, 0, 0); // Al ejecutar la funcion se popea todo del stack (si no devuelve nada)
    int stackSize = lua_gettop(L);
    printf("Stack size: %d\n", stackSize);

    //lua_pop(L, 1); // Solo si la funcion devuelve algo y ya lo use
    std::cout << "[CPP] Get printMap\n";
    lua_getglobal(L, "printMap");

    std::cout << "[CPP] Calling 'addToMap'\n";
    lua_pcall(L, 0, 0, 0);


    lua_close(L);
    return 0;
}
