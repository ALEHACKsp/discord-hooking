# discord-hooking
A simple and easy to use hooking library weaponized through discord.

This is only a PoC that was written in roughly an hour, so if you encounter any issues with the usage, please create an issue.

# Information

Discord currently uses Minihook as it's hooking library to hook it's functions onto dxgi.dll, which if taken a look into can potentially be exploited further.
The DLL is seen using 3 major Minihook functions which include : MH_CreateHook, MH_QueueHook(Enable/Disable is in 1 function, it takes a bool for whether it enables/disables the hook.), MH_ApplyQueued.
For more information about how Minihook works, check out https://github.com/TsudaKageyu/minhook.

# Usage
To use this, add the discord.h / discord.cpp files to your existing (static) DLL project, and include the stdafx.h file or copy MH_RESULT over to your project.
1. Initialize the class.
2. Call the function's as you would as if you'd use any other hooking library, and ensure DiscordHook64.dll is loaded on target process.
3. Enjoy, I tried to keep the code as clean as possible.

# Note
This only works on games that are currently running the **DiscordHook64.dll** version, any other processes utilizing the x86 target process will not work.
