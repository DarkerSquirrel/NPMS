# NPMS
Monitor For NamedPipe and MailSlot

写本工程的目的：  
procmon没有监控管道和邮件槽的功能。  
但是filemon有，但是filemon很旧了，在新的系统上运行不好。  
所以有此工程。  

此工程的采用的办法是AttachedDevice，而非minifilter。  
因为minifilter只有在指定的版本且编译为那个版本还得运行在那个版本上才行。  
AttachedDevice技术虽然旧，但支持全，且兼容以后，还可卸载。  

希望对你有用。  
