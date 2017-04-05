
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")
cc.FileUtils:getInstance():addSearchPath("res/ui/")

require "config"
require "cocos.init"
require "launch"

local function main()
    -- require("app.MyApp"):create():run()
     local sceneGame = CCScene:create()
        print("------》1")
        local layer = require("app.views.ui_template"):new()
        print(tolua.type(layer))
        -- local layer = tolua.cast(node,"cc.Node")
        -- print((layer))
        sceneGame:addChild(layer)
        CCDirector:getInstance():runWithScene(sceneGame)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
