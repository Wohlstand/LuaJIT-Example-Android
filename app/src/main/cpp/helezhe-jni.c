#include <jni.h>
#include "luajit/lua.h"
#include "luajit/lualib.h"
#include "luajit/lauxlib.h"
#include "luajit/luajit.h"

static lua_State* L = NULL;

static const char *luaDemo = "function heleCall()\n"
                             "    return \"喝了luajit2333\";\n"
                             "end\n\n";

JNIEXPORT jstring JNICALL
Java_ru_wohlsoft_helezhe_MainActivity_stringFromJNI(
    JNIEnv *env,
    jclass instance
)
{
    const char *z;
    (void)instance;
    lua_getglobal(L, "heleCall");
    lua_pcall(L, 0, 1, 0);

    z = lua_tostring(L, -1);
    lua_pop(L, 1);

    return (*env)->NewStringUTF(env, z);
}

JNIEXPORT void JNICALL
Java_ru_wohlsoft_helezhe_MainActivity_initLua(
    JNIEnv *env,
    jclass instance
)
{
    (void)instance;
    L = luaL_newstate();

    lua_pushcfunction(L, luaopen_base);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_math);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_string);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_table);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_debug);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_os);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_package);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_bit);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_ffi);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_jit);
    lua_call(L, 0, 0);
    lua_pushcfunction(L, luaopen_io);
    lua_call(L, 0, 0);

    lua_getfield(L, LUA_GLOBALSINDEX, "package");
    lua_getfield(L, -1, "preload");

    luaL_dostring(L, luaDemo);
}
