// jjhgame_ui_luaexport_common.h
#pragma once
#ifndef JJHGAME_UI_LUA_EXPORT_COMMON_H_
#define JJHGAME_UI_LUA_EXPORT_COMMON_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

#include "CCLuaEngine.h"

#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>

using namespace cocos2d;
using namespace cocos2d::extension;

// 导到lua是否debug模式
extern bool GLuaDebug;
extern bool GLuaOriginalDevelopment;
extern bool GLuaDevelopment;

void SetDevelopment(bool value);
void ExportLuaVariables(lua_State* tolua_S, ui::Widget* node);
void ReAddParent(cocos2d::Node* pNode, cocos2d::Node* pNewParent);
cocos2d::EventListenerTouchOneByOne* GetWidgetTouchListener(cocos2d::ui::Widget* pWidget);

int32_t IsLInt64(lua_State* L, int lo, tolua_Error* err);
int64_t LuaToInt64(lua_State* tolua_S, int narg, void* def);
void LuaPushInt64(lua_State* L, void* value, const char* type);

void LuaPushNotify(const char* szLuaNotify);

// 判断一个节点是否隐藏
bool IsAncestorsVisible(Node* node);

// 点是否在多边形里
// points.size >= 6
bool PolygonContainsPoint(const std::vector<int>& points, float x, float y);
//

// 设置ui是否fullscreen
void SetFullScreen(cocos2d::Node* node, bool bfull);
void SetPopUI(cocos2d::Node* node, bool bpop);

// 设置widget是否吞噬触摸
void SetWidgetSwallowTouches(cocos2d::ui::Widget* widget, bool bSwallow);

// 设置button按下是否有声音
void SetButtonSoundEnabled(cocos2d::ui::Button* button, bool able);

//得到Editbox里面的Label
cocos2d::Label* GetTextLabelFromEditbox(cocos2d::ui::EditBox* editbox);

cocos2d::Label* GetPlaceHolderFromEditbox(cocos2d::ui::EditBox* editbox);

cocos2d::ui::Widget* WidgetGetChildByName(cocos2d::ui::Widget* pWidget, const char *name);

static inline std::string& trim(std::string& str) 
{
    std::string::size_type pos = str.find_last_not_of(' ');
    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if (pos != std::string::npos) 
            str.erase(0, pos);
    }
    else
        str.erase(str.begin(), str.end());

    return str;
}

template<typename T>
struct stLua_op_t
{
    static void push_stack(lua_State* stLuaState, const T& stArg, const std::string& strTName)
    {
        tolua_pushusertype(stLuaState, (void*)&stArg, strTName.c_str());
    }
};


template<>
struct stLua_op_t<bool>
{
    static void push_stack(lua_State* stLuaState, bool bArg, const std::string& strTName)
    {
        tolua_pushboolean(stLuaState, bArg);
    }
};

template<>
struct stLua_op_t<const char*>
{
    static void push_stack(lua_State* stLuaState, const char* szArg, const std::string& strTName)
    {
        tolua_pushstring(stLuaState, szArg);
    }
};

template<>
struct stLua_op_t<const std::string&>
{
    static void push_stack(lua_State* stLuaState, const std::string& strArg, const std::string& strTName)
    {
        tolua_pushstring(stLuaState, strArg.c_str());
    }
};

template<>
struct stLua_op_t<std::string>
{
    static void push_stack(lua_State* stLuaState, const std::string& strArg, const std::string& strTName)
    {
        tolua_pushstring(stLuaState, strArg.c_str());
    }
};

template<>
struct stLua_op_t<double>
{
    static void push_stack(lua_State* stLuaState, double dArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)dArg);
    }
};

template<>
struct stLua_op_t<float>
{
    static void push_stack(lua_State* stLuaState, float fArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)fArg);
    }
};

template<>
struct stLua_op_t<int16_t>
{
    static void push_stack(lua_State* stLuaState, int16_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<uint16_t>
{
    static void push_stack(lua_State* stLuaState, uint16_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<int32_t>
{
    static void push_stack(lua_State* stLuaState, int32_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<uint32_t>
{
    static void push_stack(lua_State* stLuaState, uint32_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<int8_t>
{
    static void push_stack(lua_State* stLuaState, int8_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<uint8_t>
{
    static void push_stack(lua_State* stLuaState, uint8_t iArg, const std::string& strTName)
    {
        tolua_pushnumber(stLuaState, (lua_Number)iArg);
    }
};

template<>
struct stLua_op_t<int64_t>
{
    static void push_stack(lua_State* stLuaState, const int64_t& lArg, const std::string& strTName)
    {
        LuaPushInt64(stLuaState, const_cast<int64_t*>(&lArg), NULL);
        //tolua_pushnumber(stLuaState, (lua_Number)lArg);
    }
};

template<>
struct stLua_op_t<uint64_t>
{
    static void push_stack(lua_State* stLuaState, const uint64_t& lArg, const std::string& strTName)
    {
        LuaPushInt64(stLuaState, const_cast<uint64_t*>(&lArg), NULL);
        //tolua_pushnumber(stLuaState, (lua_Number)lArg);
    }
};


template<typename T>
struct stLua_op_t<std::list<T> >
{
    static void push_stack(lua_State* stLuaState, const std::list<T>& listArg, const std::string& strTName)
    {
        std::string::size_type i = strTName.find_first_of("<");
        std::string::size_type j = strTName.find_last_of(">");
        std::string strVName = strTName.substr(i + 1, j - i - 1);

        lua_newtable(stLuaState);
        typename std::list<T>::const_iterator it = listArg.begin();
        for (int i = 1; it != listArg.end(); ++it, ++i)
        {
            stLua_op_t<int>::push_stack(stLuaState, i, "int");
            stLua_op_t<T>::push_stack(stLuaState, *it, strVName);
            lua_settable(stLuaState, -3);
        }
    }
};

template<typename K, typename V>
struct stLua_op_t<std::map<K, V> >
{
    static void push_stack(lua_State* stLuaState, const std::map<K, V>& mapArg, const std::string& strTName)
    {
        std::string::size_type i = strTName.find_first_of("<");
        std::string::size_type j = strTName.find_last_of(">");
        std::string strRName = strTName.substr(i + 1, j - i - 1);
        i = strRName.find_first_of(",");
        std::string strKTName = strRName.substr(0, i);
        std::string strVTName = strRName.substr(i + 1);
        lua_newtable(stLuaState);
        typename std::map<K, V>::const_iterator it = mapArg.begin();
        for (; it != mapArg.end(); ++it)
        {
            stLua_op_t<K>::push_stack(stLuaState, it->first, strKTName);
            stLua_op_t<V>::push_stack(stLuaState, it->second, strVTName);
            lua_settable(stLuaState, -3);
        }
    }
};

template<typename K, typename V>
struct stLua_op_t<std::pair<K, V> >
{
    static void push_stack(lua_State* stLuaState, const std::pair<K, V>& pairArg, const std::string& strTName)
    {
        std::string::size_type i = strTName.find_first_of("<");
        std::string::size_type j = strTName.find_last_of(">");
        std::string strRName = strTName.substr(i + 1, j - i - 1);
        i = strRName.find_first_of(",");
        std::string strKTName = strRName.substr(0, i);
        std::string strVTName = strRName.substr(i + 1);
        lua_newtable(stLuaState);
        stLua_op_t<std::string>::push_stack(stLuaState, "first", "std::string");
        stLua_op_t<K>::push_stack(stLuaState, pairArg.first, strKTName);
        lua_settable(stLuaState, -3);
        stLua_op_t<std::string>::push_stack(stLuaState, "second", "std::string");
        stLua_op_t<V>::push_stack(stLuaState, pairArg.second, strVTName);
        lua_settable(stLuaState, -3);
    }
};

template<typename T>
struct stLua_op_t<std::set<T> >
{
    static void push_stack(lua_State* stLuaState, const std::set<T>& setArg, const std::string& strTName)
    {
        std::string::size_type i = strTName.find_first_of("<");
        std::string::size_type j = strTName.find_last_of(">");
        std::string strVName = strTName.substr(i + 1, j - i - 1);

        lua_newtable(stLuaState);
        typename std::set<T>::const_iterator it = setArg.begin();
        for (int i = 1; it != setArg.end(); ++it, ++i)
        {
            stLua_op_t<int>::push_stack(stLuaState, i, "int");
            stLua_op_t<T>::push_stack(stLuaState, *it, strVName);
            lua_settable(stLuaState, -3);
        }
    }
};

template<typename T>
struct stLua_op_t<std::vector<T> >
{
    static void push_stack(lua_State* stLuaState, const std::vector<T>& vecArg, const std::string& strTName)
    {
        std::string::size_type i = strTName.find_first_of("<");
        std::string::size_type j = strTName.find_last_of(">");
        std::string strVName = strTName.substr(i + 1, j - i - 1);

        lua_newtable(stLuaState);
        typename std::vector<T>::const_iterator it = vecArg.begin();
        for (int i = 1; it != vecArg.end(); ++it, ++i)
        {
            stLua_op_t<int>::push_stack(stLuaState, i, "int");
            stLua_op_t<T>::push_stack(stLuaState, *it, strVName);
            lua_settable(stLuaState, -3);
        }
    }
};

template<typename K, typename V>
struct stLua_op_t < std::unordered_map<K, V> >
{
    static void push_stack(lua_State* lua_state, const std::unordered_map<K, V>& map_arg, const std::string& type_name)
    {
        auto i = type_name.find_first_of("<");
        auto j = type_name.find_last_of(">");
        auto r_name = type_name.substr(i + 1, j - i - 1);
        i = r_name.find_first_of(",");
        auto k_name = r_name.substr(0, i);
        auto v_name = r_name.substr(i + 1);

        lua_newtable(lua_state);
        for (auto it = map_arg.begin(); it != map_arg.end(); ++it)
        {
            stLua_op_t<K>::push_stack(lua_state, it->first, k_name);
            stLua_op_t<V>::push_stack(lua_state, it->second, v_name);
            lua_settable(lua_state, -3);
        }
    }
};


template<>
struct stLua_op_t<void*>
{
    static void push_stack(lua_State* stLuaState, void* stArg, const std::string& strTName)
    {
        tolua_pushuserdata(stLuaState, stArg);
    }
};


template<typename T>
struct stLua_op_t<T*>
{
    static void push_stack(lua_State* stLuaState, T* stArg, const std::string& strTName)
    {
        ssize_t pos = strTName.find('*');
        if (pos == std::string::npos)
        {
            tolua_pushusertype(stLuaState, stArg, strTName.c_str());
        }
        else
        {
            std::string strRTName = strTName.substr(0, pos);
            strRTName = trim(strRTName);
            tolua_pushusertype(stLuaState, stArg, strRTName.c_str());
        }
    }
};

template<typename T>
struct stLua_op_t<const T*>
{
    static void push_stack(lua_State* stLuaState, const T* stArg, const std::string& strTName)
    {
        stLua_op_t<T*>::push_stack(stLuaState, (T*)stArg, strTName.c_str());
    }
};



template<typename T>
struct stLua_op_t<T&>
{
    static void push_stack(lua_State* stLuaState, const T& stArg, const std::string& strTName)
    {
        tolua_pushusertype(stLuaState, &stArg, strTName.c_str());
    }
};


#define TYPENONE 0
#define TYPEINT 1
#define TYPEBOOL 2
#define TYPESTRING 3
#define TYPEUSERDATA 4
#define TYPEBIGINT 5
#define TYPESTL 6
#define TYPEBYTES 7
#define TYPEFLOAT 8

struct stUserData
{
    const char*     m_szClassName;
    void*           m_pData;
};

struct stUserDataToLua
{
    union unUserData
    {
        stUserData  m_stUserData;
        int64_t     m_lData;
        int32_t     m_iData;
        const char* m_szData;
        float       m_fData;
        int32_t     m_stlData;
    }   m_unUserData;
    char            m_btType;
    int32_t         m_len;

    stUserDataToLua() : m_btType(TYPENONE)
    {}
    stUserDataToLua(float i) : m_btType(TYPEFLOAT)
    {
        m_unUserData.m_fData = i;
    }
    stUserDataToLua(int32_t i) : m_btType(TYPEINT)
    {
        m_unUserData.m_iData = i;
    }
    stUserDataToLua(uint32_t ui) : m_btType(TYPEINT)
    {
        m_unUserData.m_iData = ui;
    }
    stUserDataToLua(bool b) : m_btType(TYPEBOOL)
    {
        m_unUserData.m_iData = (int32_t)b;
    }
    stUserDataToLua(int64_t l) : m_btType(TYPEBIGINT)
    {
        m_unUserData.m_lData = l;
    }
    stUserDataToLua(uint64_t ul) : m_btType(TYPEBIGINT)
    {
        m_unUserData.m_lData = ul;
    }

    stUserDataToLua(const char* szStr) : m_btType(TYPESTRING)
    {
        m_unUserData.m_szData = szStr;
    }
    stUserDataToLua(const char* szStr, int len) : m_btType(TYPEBYTES)
    {
        m_unUserData.m_szData = szStr;
        m_len = len;
    }
    stUserDataToLua(const std::string& strStr) : m_btType(TYPESTRING)
    {
        m_unUserData.m_szData = strStr.c_str();
    }

    stUserDataToLua(void* pUserData, const char* szUserDataType) : m_btType(TYPEUSERDATA)
    {
        m_unUserData.m_stUserData.m_szClassName = szUserDataType;
        m_unUserData.m_stUserData.m_pData = pUserData;
    }

    template<typename T>
    stUserDataToLua(const std::vector<T>& stStlData, const char* szType) : m_btType(TYPESTL)
    {
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        lua_State *pState = pStack->getLuaState();
        m_unUserData.m_stlData = lua_gettop(pState);
        stLua_op_t<std::vector<T>>::push_stack(pState, stStlData, szType);
    }

    template<typename K, typename V>
    stUserDataToLua(const std::map<K,V>& stStlData, const char* szType) : m_btType(TYPESTL)
    {
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        lua_State *pState = pStack->getLuaState();
        m_unUserData.m_stlData = lua_gettop(pState);
        stLua_op_t<std::map<K,V>>::push_stack(pState, stStlData, szType);
    }

    template<typename K, typename V>
    stUserDataToLua(const std::pair<K, V>& stStlData, const char* szType) : m_btType(TYPESTL)
    {
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        lua_State *pState = pStack->getLuaState();
        m_unUserData.m_stlData = lua_gettop(pState);
        stLua_op_t<std::pair<K, V>>::push_stack(pState, stStlData, szType);
    }

    template<typename T>
    stUserDataToLua(const std::set<T>& stStlData, const char* szType) : m_btType(TYPESTL)
    {
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        lua_State *pState = pStack->getLuaState();
        m_unUserData.m_stlData = lua_gettop(pState);
        stLua_op_t<std::set<T>>::push_stack(pState, stStlData, szType);
    }

    template<typename T>
    stUserDataToLua(const std::list<T>& stStlData, const char* szType) : m_btType(TYPESTL)
    {
        LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
        lua_State *pState = pStack->getLuaState();
        m_unUserData.m_stlData = lua_gettop(pState);
        stLua_op_t<std::list<T>>::push_stack(pState, stStlData, szType);
    }

};


void RealSendMessageToLua(const char* szLuaType, ...);

inline void SendMessageToLua(const char* szLuaType)
{
    stUserDataToLua s = stUserDataToLua();
    RealSendMessageToLua(szLuaType, &s);
}
template<typename T1>
inline void SendMessageToLua(const char* szLuaType, T1 t1)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    RealSendMessageToLua(szLuaType, &s1, &s);
}
template<typename T1, typename T2>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s);
}
template<typename T1, typename T2, typename T3>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s);
}
template<typename T1, typename T2, typename T3, typename T4>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3, T4 t4)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    stUserDataToLua s4 = stUserDataToLua(t4);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s4, &s);
}
template<typename T1, typename T2, typename T3, typename T4, typename T5>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    stUserDataToLua s4 = stUserDataToLua(t4);
    stUserDataToLua s5 = stUserDataToLua(t5);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s4, &s5, &s);
}
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    stUserDataToLua s4 = stUserDataToLua(t4);
    stUserDataToLua s5 = stUserDataToLua(t5);
    stUserDataToLua s6 = stUserDataToLua(t6);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s4, &s5, &s6, &s);
}
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    stUserDataToLua s4 = stUserDataToLua(t4);
    stUserDataToLua s5 = stUserDataToLua(t5);
    stUserDataToLua s6 = stUserDataToLua(t6);
    stUserDataToLua s7 = stUserDataToLua(t7);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s);
}
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline void SendMessageToLua(const char* szLuaType, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
{
    stUserDataToLua s  = stUserDataToLua();
    stUserDataToLua s1 = stUserDataToLua(t1);
    stUserDataToLua s2 = stUserDataToLua(t2);
    stUserDataToLua s3 = stUserDataToLua(t3);
    stUserDataToLua s4 = stUserDataToLua(t4);
    stUserDataToLua s5 = stUserDataToLua(t5);
    stUserDataToLua s6 = stUserDataToLua(t6);
    stUserDataToLua s7 = stUserDataToLua(t7);
    stUserDataToLua s8 = stUserDataToLua(t8);
    RealSendMessageToLua(szLuaType, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s);
}

void LuaExportInit();
//

#endif //AURORAGAME_UI_LUA_EXPORT_COMMON_H_