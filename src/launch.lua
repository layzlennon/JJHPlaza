-- launch.lua
local function _launch_load_base_lua( ... )
    require "common.utils"
end

local function init( ... )
    _launch_load_base_lua()
end

init()