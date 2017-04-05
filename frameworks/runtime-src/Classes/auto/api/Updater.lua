
--------------------------------
-- @module Updater
-- @parent_module 

--------------------------------
-- 
-- @function [parent=#Updater] getUpdateInfo 
-- @param self
-- @param #char url
-- @return char#char ret (return value: char)
        
--------------------------------
--  @brief Sets delegate, the delegate will receive messages
-- @function [parent=#Updater] setDelegate 
-- @param self
-- @param #cc.UpdaterDelegateProtocol delegate
-- @return Updater#Updater self (return value: cc.Updater)
        
--------------------------------
--  @brief Register script handler, the hander will receive messages
-- @function [parent=#Updater] registerScriptHandler 
-- @param self
-- @param #int handler
-- @return Updater#Updater self (return value: cc.Updater)
        
--------------------------------
-- 
-- @function [parent=#Updater] removeDirectory 
-- @param self
-- @param #char path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, cc.__Array         
-- @overload self, char, char, char, bool         
-- @overload self, char, char         
-- @overload self, char         
-- @function [parent=#Updater] update
-- @param self
-- @param #char zipUrl
-- @param #char zipFile
-- @param #char unzipTmpDir
-- @param #bool resetBeforeUnZIP
-- @return Updater#Updater self (return value: cc.Updater)

--------------------------------
-- 
-- @function [parent=#Updater] unregisterScriptHandler 
-- @param self
-- @return Updater#Updater self (return value: cc.Updater)
        
--------------------------------
--  @brief Gets connection time out in secondes
-- @function [parent=#Updater] getConnectionTimeout 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#Updater] createDirectory 
-- @param self
-- @param #char path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  @brief Sets connection time out in seconds
-- @function [parent=#Updater] setConnectionTimeout 
-- @param self
-- @param #unsigned int timeout
-- @return Updater#Updater self (return value: cc.Updater)
        
--------------------------------
-- 
-- @function [parent=#Updater] Updater 
-- @param self
-- @return Updater#Updater self (return value: cc.Updater)
        
return nil
