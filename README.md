# discord-hooking
A simple and easy to use hooking library weaponized through discord.

This is only a PoC that was written in roughly an hour, so if you encounter any issues with the usage, please create an issue.

# Usage
To use this, add the discord.h / discord.cpp files to your existing (static) DLL project, and include the stdafx.h file or copy MH_RESULT over to your project.
1. Initialize the class.
2. Call the function's as you would as if you'd use any other hooking library, and ensure DiscordHook64.dll is loaded on target process.

# Note
This only works on games that are currently running the **DiscordHook64.dll** version, any other processes utilizing the x86 target process will not work.
