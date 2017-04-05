-- ui_template.lua
--region ui_teamplate.lua

--***模板定义***
--实例对象
local l_uiTemplateInstance = nil
-- 声明类，继承ui_base
local cls_uiTemplate = class("ui_template", ui_base)
cls_uiTemplate.uiJson = "TemplateUI.csb"

--[Comment]
--构造函数
function cls_uiTemplate:ctor()
    local self = self.super.ctor(self)
    --声明/定义成员变量
    --如：self.m_isLocal = true
    --获取ui展示需要的数据
    --如：self.m_dailyDungeonCfg = CDailyDungeonCfgMgr:GetInstance()
    self:LoadResource()
    --初始化ui界面
    self:InitUI()

    l_uiTemplateInstance = self
    print(tolua.type(self).." ui_template")
    return self
end

function cls_uiTemplate:LoadResource()
    
end

function cls_uiTemplate:ClearResource()
    
end

--[Comment]
--初始化ui
function cls_uiTemplate:InitUI()
    --初始化ui展现
    -- self.Button_1:setVisible(false)
end

--[Comment]
--刷新ui展现（可选）
function cls_uiTemplate:RefreshUI()
    --用于即时更新ui的展现（比如从不能领奖更新为可以领奖）
    --如若有多个独立局部刷新，则建议每个局部刷新定义成一个成员函数，再由RefreshUI来统一调用
end

--[Comment]
--在界面展示之前要做的事情（可选|自动调用）
function cls_uiTemplate:OnEnter()
    self.super.OnEnter(self)
    --一些初始化的操作
    --把实例注册到ui_manager
end

--[Comment]
--在界面恢复展示时调用的方法（可选|手动调用）
--注：此方法需要自己调用show()方法才会触发
--show()和hide()方法由ui_base提供
function cls_uiTemplate:OnShow()
    --在界面恢复展示时需要的操作
end

--[Comment]
--关闭界面（可选，ui_base有close）
function cls_uiTemplate:close()
    --关闭界面时的操作
    --如：移除自身，将自身变量重置以及后续的一些操作等
    -- ActionHideTanChuang(self.m_Panel_all, function()
        self:removeFromParent()
    -- end)
end

--[Comment]
--在释放界面前要做的事情（必须|自动调用）
function cls_uiTemplate:OnExit()
    self.super.OnExit(self)
    --重置变量
    self:ResetVariables()
    --其他
    self:ClearResource()
end

--[Comment]
--重置需要重置的变量，杜绝reloadfile
function cls_uiTemplate:ResetVariables()
    l_uiTemplateInstance = nil
end

-- --[Comment]
-- --统一的创建界面入口
-- function ShowTemplateUI()
--     --普通

--     --[[if not l_uiTemplateInstance then
--         l_uiTemplateInstance = cls_uiTemplate:new()
--         AddToTownScene({ui=l_uiTemplateInstance})
--     else
--         l_uiTemplateInstance:show()
--     end
--     ActionShowTanChuang(l_uiTemplateInstance.m_Panel_all)
--     ]]

--     --common title
--     --require "ui/tiny_ui/ui_common_title"
--     --ShowCommonTitle({"template"}, "template")
-- end

-- --[Comment]
-- --统一的获取界面实例入口
-- function GetTemplateInstance()
--     return l_uiTemplateInstance
-- end
--其他的一些方法就按照界面需求来定义

return cls_uiTemplate
--endregion