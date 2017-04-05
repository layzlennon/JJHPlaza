-- launch.lua
local function _launch_load_base_lua( ... )
    require "common.utils"
    require "ui_base"
end

local function init( ... )
    _launch_load_base_lua()
end

init()