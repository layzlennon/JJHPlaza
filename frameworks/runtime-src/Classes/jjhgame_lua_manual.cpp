// jjhgame_lua_manual.cpp
extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "tolua_fix.h"
#include "CCLuaEngine.h"
#include "spine/spine-cocos2dx.h"
#include "jjhgame_lua_manual.h"
#include "jjhgame_ui_luaexport_common.h"
#include "cocos/scripting/lua-bindings/manual/LuaBasicConversions.h"



static void extend_common_split(lua_State* L)
{
    //tolua_function(L, "split", lua_common_split);
}

static int handleUIEvent_int(int handler, cocos2d::Ref* sender, int eventType)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    stack->pushObject(sender, "cc.Ref");
    stack->pushInt(eventType);

    stack->executeFunctionByHandler(handler, 2);

    return 0;
}

static int handleUIEvent(int handler, cocos2d::Ref* sender)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    stack->pushObject(sender, "cc.Ref");

    stack->executeFunctionByHandler(handler, 1);

    return 0;
}

static int handleUIEvent(int handler, int eventType)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    stack->pushInt(eventType);

    stack->executeFunctionByHandler(handler, 1);

    return 0;
}

static int lua_PolygonContainsPoint(lua_State* tolua_S)
{
    int argc = 0;
    bool ok = true;
    bool ret = false;

    argc = lua_gettop(tolua_S);

    if (argc == 3)
    {
        std::vector<int> arg0;
        ok &= luaval_to_std_vector_int(tolua_S, 1, &arg0);
        if (ok)
        {
            float x = ((float)tolua_tonumber(tolua_S, 2, 0));
            float y = ((float)tolua_tonumber(tolua_S, 3, 0));
            ret = PolygonContainsPoint(arg0, x, y);
        }

        lua_pushboolean(tolua_S, ret);
    }

    return ok;
}

static void extendPolygonContainsPoint(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "PolygonContainsPoint");
    lua_pushcfunction(tolua_S, lua_PolygonContainsPoint);
    lua_rawset(tolua_S, -3);
}



static int lua_cocos2dx_ui_Widget_addClickEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;
    cocos2d::ui::Widget* self = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccui.Widget", 0, &tolua_err)) goto tolua_lerror;
#endif

    self = static_cast<cocos2d::ui::Widget*>(tolua_tousertype(L, 1, 0));

#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(L, "invalid 'self' in function 'lua_cocos2dx_Widget_addTouchEventListener'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif

        LUA_FUNCTION handler = (toluafix_ref_function(L, 2, 0));

        self->addClickEventListener([=](cocos2d::Ref* ref){
            handleUIEvent(handler, ref);
        });

        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }

    luaL_error(L, "'addClickEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'addTouchEventListener'.", &tolua_err);
    return 0;
#endif
}

static void extend_widget_addClickEventListener(lua_State* L)
{
    lua_pushstring(L, "ccui.Widget");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "addClickEventListener", lua_cocos2dx_ui_Widget_addClickEventListener);
    }
    lua_pop(L, 1);
}


static int tolua_act_ExportLuaVariables(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S, 1, "ccui.Widget", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ui::Widget* node = ((ui::Widget*)  tolua_tousertype(tolua_S, 1, 0));
        {
            ExportLuaVariables(tolua_S, node);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror :
    tolua_error(tolua_S, "#ferror in function 'ExportLuaVariables'.", &tolua_err);
    return 0;
#endif
}


int register_all_jjhgame_manual(struct lua_State* L)
{
    if (nullptr == L)
        return 0;

    tolua_function(L, "ExportLuaVariables", tolua_act_ExportLuaVariables);
    extendPolygonContainsPoint(L);
    return 0;
}
