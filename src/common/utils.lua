-- util.lua
module("common.utils",package.seeall)

--[Comment]
--将node下的节点导出到Lua成员变量
--@return nil
function ExportLuaVariables_lua( node )
    if tolua.getpeer(node) == nil then
        tolua.setpeer(node, {})
    end
    ExportLuaVariables(node)
end