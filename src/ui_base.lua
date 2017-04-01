-- ui_base.lua
ui_base = class("ui_base")

require "ui/ui_manager"

function ui_base:ctor()
    local ret = self
    self.uiJson = self.uiJson or "ui/CommonUI/CommonBase.csb"
    if self.uiJson then
        local uiWidget = nil
        if not cc.FileUtils:getInstance():isFileExist(self.uiJson) then
            local msg_box_info = common.utils.lang("lang_text_1")
            PushNotify(self.uiJson .. msg_box_info)
            return ret
        end
        uiWidget = cc.CSLoader:createNode(self.uiJson):getChildren()[1]
        uiWidget:removeFromParent()
        tolua.setpeer(uiWidget, self)
        ExportLuaVariables_lua(uiWidget)
        uiWidget : RegisterEnterExit()
        ret = uiWidget
    end

    -- 常用c++里的对象
    self.Protocol = CPP():GetLogicProtoMgr()
    self.CachePlayer = CPP():GetMyPlayerCache()
    if self.CachePlayer then
        self.CachePlayerBase = self.CachePlayer.m_stPlayerBaseInfo
    end
    self.EquipExtCfg = CPP():GetEquipExtCfgMgr()
    self.EquipCfg = CPP():GetEquipCfgMgr()
    self.ItemCfg = CPP():GetItemCfgMgr()
    self.MyUin = CPP():GetBaseProtoMgr() : GetMyUin()
    self.VipCfg = CPP():GetVipCfgMgr()
    self.m_generalConfig = CPP():GetGeneralCfgMgr()
    self.m_generalManager = CPP():GetGeneralMgr()

    -- 隐藏模板层
    if self.m_Panel_template then
        self.m_Panel_template:setVisible(false)
    end

    return ret
end

function ui_base:RegisterEnterExit()
    local function onLayerEvent(event)
        if "exit" == event then
            self : OnExit()
        elseif "enter" == event then
            self : OnEnter()
        end
    end
    self : registerScriptHandler(onLayerEvent)
end

function ui_base:OnEnter()
    --打开全屏的界面时隐藏其他界面
    if self._fullScreen then
        CheckUIShowOrHide()
    end
end

function ui_base:OnExit()
    --将其从已打开的模块中去除
    OnClosedUIModule(self)
    --移除该ui所有注册的事件
    removeNotifys(self)
    --关闭全屏界面时打开最上层界面
    if self._fullScreen then
        CheckUIShowOrHide()
    end
end

function ui_base:show()
    self:setVisible(true)
    --在显示出来时候需要调用的方法
    if self.OnShow then
        self:OnShow()
    end
end

function ui_base:hide()
    self:setVisible(false)
end

--[Comment]
--关闭方法
function ui_base:close()
    self:removeFromParent()
end