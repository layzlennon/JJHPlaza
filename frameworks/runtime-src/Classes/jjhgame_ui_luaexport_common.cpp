// jjhgame_ui_luaexport_common.cpp
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "jjhgame_ui_luaexport_common.h"
#include "LuaBasicConversions.h"
USING_NS_CC;
#if defined( _DEBUG ) || defined( DEBUG ) || defined (__DEBUG__)
bool GLuaDebug = true;
#else
bool GLuaDebug = false;
#endif

#if CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM
static bool IsProcessCommand(const char* szCmd)
{
    if (szCmd == NULL)
    {
        return false;
    }

    char *pCmdLine = GetCommandLineA();//joewan
    return strstr(pCmdLine, szCmd) - pCmdLine >= 0;

    /*
    char* token = strtok(pCmdLine, " ");
    while (token != NULL)
    {
        if (strcasecmp(token, szCmd) == 0)
        {
            return true;
        }

        token = strtok(NULL, " ");
    }

    return false;
    //*/
}

bool GLuaDevelopment = IsProcessCommand("-developer");
#else
bool GLuaDevelopment = false;
#endif
bool GLuaOriginalDevelopment = GLuaDevelopment;

using namespace cocos2d;
using namespace cocos2d::extension;

static LUA_FUNCTION s_ReceiveCPPMessageHandler = 0;

void ReAddParent(cocos2d::Node* pNode, cocos2d::Node* pNewParent)
{
    if (pNode == nullptr || pNewParent == nullptr)
        return;
    if (pNode->getParent() == pNewParent)
        return;
    pNode->retain();
    pNode->removeFromParentAndCleanup(false);
    pNewParent->addChild(pNode);
    pNode->release();
}

bool IsAncestorsVisible(Node* node)
{
    if (nullptr == node)
    {
        return true;
    }

    if (node->isVisible() == false)
    {
        return false;
    }

    Node* parent = node->getParent();

    if (parent && !parent->isVisible())
    {
        return false;
    }
    return IsAncestorsVisible(parent);
}

bool CalculateSegmentIntersection2D(const Vec2& SegmentStartA, const Vec2& SegmentEndA, const Vec2& SegmentStartB, const Vec2& SegmentEndB)
{
    const Vec2 VectorA = SegmentEndA - SegmentStartA;
    const Vec2 VectorB = SegmentEndB - SegmentStartB;

    const float S = (-VectorA.y * (SegmentStartA.x - SegmentStartB.x) + VectorA.x * (SegmentStartA.y - SegmentStartB.y)) / (-VectorB.x * VectorA.y + VectorA.x * VectorB.y);
    const float T = (VectorB.x * (SegmentStartA.y - SegmentStartB.y) - VectorB.y * (SegmentStartA.x - SegmentStartB.x)) / (-VectorB.x * VectorA.y + VectorA.x * VectorB.y);

    const bool bIntersects = S >= 0 && S <= 1 && T >= 0 && T <= 1;

    return bIntersects;
}

bool PolygonContainsPoint(const std::vector<int>& points, float x, float y)
{
    Vec2 StartB(x, y);
    Vec2 EndB(9999, 9999);

    int iIntersection = 0;
    int count = points.size();
    for (int i = 0; i < count; i += 2) {

        Vec2 NextA((float)(points[(i + 2) % count]), (float)(points[(i + 3) % count]));
        Vec2 A((float)(points[i]), (float)(points[i + 1]));
        if (CalculateSegmentIntersection2D(A, NextA, StartB, EndB))
        {
            ++iIntersection;
        }
    }
    return iIntersection%2;
}

void SetFullScreen(cocos2d::Node* node, bool bfull)
{
    //cocos2dx 3.6
    //if (node)
    //{
    //    node->setFullScreen(bfull);
    //}
}

cocos2d::ui::Widget* WidgetGetChildByName(cocos2d::ui::Widget* pWidget, const char *name)
{
    for (auto& child : pWidget->getChildren())
    {
        if (child)
        {
            cocos2d::ui::Widget* widgetChild = dynamic_cast<cocos2d::ui::Widget*>(child);

            if (widgetChild == NULL) continue;

            if (strcmp(widgetChild->getName().c_str(), name) == 0)
            {
                return widgetChild;
            }
            else if (widgetChild->getChildrenCount() > 0)
            {
                widgetChild = WidgetGetChildByName(widgetChild, name);
                if (widgetChild)
                    return widgetChild;
            }
        }
    }
    return nullptr;
}

void SetPopUI(cocos2d::Node* node, bool bpop)
{
    //cocos2dx 3.6
    //if (node)
    //{
    //  node->setPopUI(bpop);
    //}
}



void RealExportLuaVar(lua_State* L, ui::Widget* curNode)
{
    auto& children = curNode->getChildren();
    for (const auto &child : children)
    {
        ui::Widget* pNode = dynamic_cast<ui::Widget*>(child);
        if (pNode)
        {
            if (!pNode->getName().empty())
            {
                const char* szLuaTypeName = getLuaTypeName(pNode, "");
                luaL_getmetatable(L, szLuaTypeName); /* L : self mt */
                if (!lua_isnil(L, -1))
                {
                    lua_pop(L, 1);                   /* L : self */

                    int ID = (int)pNode->_ID;
                    int* luaID = &pNode->_luaID;
                    toluafix_pushusertype_ccobject(L, ID, luaID, (void*)pNode, szLuaTypeName);      /* L : self ud */

                    //tolua_pushusertype(L, pNode, szLuaTypeName);     // fuck the tolua_pushusertype
                    lua_setfield(L, -2, pNode->getName().c_str());   /* self[pNode->getName()] = ud, L : self */
                }
                else
                {
                    lua_pop(L, 1);                  /* L : self */
                }


            }
            RealExportLuaVar(L, pNode);
        }
    }
}

void ExportLuaVariables(lua_State* tolua_S, ui::Widget* node)
{
    if (node == NULL)
        return;

    if (tolua_S)
    {
        if (lua_gettop(tolua_S) < 1)
            return;

        lua_getfenv(tolua_S, -1);
        if (lua_rawequal(tolua_S, -1, TOLUA_NOPEER))
            return;

        RealExportLuaVar(tolua_S, node);
    }
}

void LuaPushNotify(const char* szLuaNotify)
{
    SendMessageToLua("ENUM_UI_PUSH_NOTIFY", szLuaNotify);
}

void LuaExportInit()
{
    s_ReceiveCPPMessageHandler = 0;
}

void RealSendMessageToLua(const char* szLuaType, ...)
{
    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
    lua_State *pState = pStack->getLuaState();

    //#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    //    static int i = 0;
    //    ++i;
    //    if (i >= 1)
    //    {
    //        lua_gc(pState, LUA_GCCOLLECT, 0);
    //        i = 0;
    //    }
    //#endif

    //if (s_ReceiveCPPMessageHandler == 0)
    //{
    //    lua_getglobal(pState, "ReceiveCPPMessage");                             /* stack: ... fun */
    //    s_ReceiveCPPMessageHandler = toluafix_ref_function(pState, lua_gettop(pState), 0);       /* stack: ... fun */
    //    lua_pop(pState, 1);                                                     /* stack: ... */
    //}
    //if (s_ReceiveCPPMessageHandler == 0)
    //{
    //    return;
    //}

    lua_getglobal(pState, "ReceiveCPPMessage");       /* query function by name, stack: function */
    if (!lua_isfunction(pState, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", "ReceiveCPPMessage");
        lua_pop(pState, 1);
        return;
    }

    int iLuaArgNum = 1;
    pStack->pushString(szLuaType);                                                  /* L: ... uiType */

    va_list ap;
    va_start(ap, szLuaType);

    stUserDataToLua* stData = va_arg(ap, stUserDataToLua*);

    while (stData->m_btType != TYPENONE)
    {
        switch (stData->m_btType)
        {
        case TYPEFLOAT:
            ++iLuaArgNum;
            pStack->pushFloat(stData->m_unUserData.m_fData);                      /* L: ... uiType arg1 ... */
            break;
        case TYPEINT:
            ++iLuaArgNum;
            pStack->pushInt(stData->m_unUserData.m_iData);                      /* L: ... uiType arg1 ... */
            break;
        case TYPEBOOL:
            ++iLuaArgNum;
            pStack->pushBoolean((bool)stData->m_unUserData.m_iData);                        /* L: ... uiType arg1 ... */
            break;
        case TYPESTRING:
            ++iLuaArgNum;
            pStack->pushString(stData->m_unUserData.m_szData);                  /* L: ... uiType arg1 ... */
            break;
        case TYPEBYTES:
            ++iLuaArgNum;
            pStack->pushString(stData->m_unUserData.m_szData, stData->m_len);                  /* L: ... uiType arg1 ... */
            break;
        case TYPEUSERDATA:
            ++iLuaArgNum;

            luaL_getmetatable(pState, stData->m_unUserData.m_stUserData.m_szClassName);                                 /* stack: mt */
            if (lua_isnil(pState, -1)) { /* NOT FOUND metatable */
                //AURORA_LOG(INFO) << "fuck you! the class name = " << stData->m_unUserData.m_stUserData.m_szClassName << " is nil!";
                lua_pop(pState, 1);
                pStack->clean();
                return;
            }else{
                lua_pop(pState, 1);
            }

            tolua_pushusertype(pState, stData->m_unUserData.m_stUserData.m_pData, stData->m_unUserData.m_stUserData.m_szClassName);     /* L: ... uiType arg1 ... */
            break;
        case TYPEBIGINT:
            ++iLuaArgNum;
            LuaPushInt64(pState, &(stData->m_unUserData.m_lData), NULL);
            break;
        case TYPESTL:
            ++iLuaArgNum;
            lua_pushvalue(pState, stData->m_unUserData.m_stlData + 1);
            break;
        default:
            break;
        }
        stData = va_arg(ap, stUserDataToLua*);
    }
    va_end(ap);

    //
    //if (pStack->executeFunction(s_ReceiveCPPMessageHandler, iLuaArgNum, 0, nullptr) != 0)
    //{
    //    lua_pop(pState, iLuaArgNum); // remove function and arguments
    //}
    pStack->executeFunction(iLuaArgNum);
    pStack->clean();
}


int32_t IsLInt64(lua_State* L, int lo, tolua_Error* err)
{
    if (tolua_isnumber(L, lo, 0, err))
    {
        return 1;
    }
    else
    {
        //return (!tolua_isvaluenil(L, lo, err) && tolua_isusertype(L, lo, "int64_t", 0, err));
        return (!tolua_isvaluenil(L, lo, err) && lua_isstring(L, lo));
    }
    return 0;
};

int64_t LuaToInt64(lua_State* tolua_S, int narg, void* def)
{
    tolua_Error tolua_err;
    if (tolua_isstring(tolua_S, narg, 0, &tolua_err))
    {
        //int64_t l = *(int64_t*)tolua_tousertype(tolua_S, narg, 0);
        //return l;
        //void* p = lua_touserdata(tolua_S, narg);
        //int64_t n = (intptr_t)p;
        //return n;

        /* old version
        size_t len = 0;
        const uint8_t * str = (const uint8_t *)lua_tolstring(tolua_S, narg, &len);
        uint64_t n64 = 0;
        for (int i = 0; i < (int)len; i++) {
            n64 |= (uint64_t)str[i] << (i * 8);
        }
        */

        size_t len = 0;
        const uint8_t * str = (const uint8_t *)lua_tolstring(tolua_S, narg, &len);
        int64_t n64 = 0;
        int i = 0;
        int flag = 1;
        if (len > 0 && str[0] == '-')
        {
            flag = -1;
            i = 1;
        }
        for (; i < (int)len; i++) {
            n64 = n64 * 10 + (str[i] - '0');
        }

        n64 = n64 * flag;
        return n64;
    }
    else if (tolua_isnumber(tolua_S, narg, 0, &tolua_err))
    {
        return ((uint64_t)tolua_tonumber(tolua_S, narg, 0));
    }

    return 0;
}

void LuaPushInt64(lua_State* L, void* value, const char* type)
{
    if (value == NULL)
    {
        lua_pushnil(L);
    }
    else
    {
        /* old version
        unsigned char buffer[8];
        uint64_t n = *(uint64_t*)value;
        for (int i = 0; i < 8; i++) {
            buffer[i] = (n >> (i * 8)) & 0xff;
        }
        lua_pushlstring(L, (const char*)buffer, 8);
        */

        unsigned char buffer[32];
        int64_t n = *(int64_t*)value;
        int l = 0;
        if (n == 0)buffer[l++] = '0';
        bool neg = false;
        if (n < 0)
        {
            n = -n;
            neg = true;
        }
        while (n > 0)
        {
            buffer[l++] = n % 10 + '0';
            n /= 10;
        }
        if (neg)
        {
            buffer[l++] = '-';
        }
        for (int i = 0, tl = l / 2; i < tl; i++)std::swap(buffer[i], buffer[l - i - 1]);
        lua_pushlstring(L, (const char*)buffer, l);

        //lua_pushlightuserdata(L, (void*)(intptr_t)(*(int64_t*)value));
        //tolua_pushusertype(L, value, "int64_t");
    }
}

int handleACTEvent(int handler, cocos2d::Ref* sender, int eventType)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    stack->pushObject(sender, "cc.Ref");
    stack->pushInt(eventType);

    stack->executeFunctionByHandler(handler, 2);
    stack->clean();

    return 0;
}

int handleEmptyArgACTFunc(int handler)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    stack->executeFunctionByHandler(handler, 0);
    stack->clean();

    return 0;
}

void SetDevelopment(bool value)
{
    GLuaDevelopment = value;
}
