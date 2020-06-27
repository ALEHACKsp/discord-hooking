#include "discord.h"

discord* hook;

uintptr_t discord::GetDiscordModuleAddress()
{
	static uintptr_t hDiscordBaseAddress = 0;

	if (!hDiscordBaseAddress)
		hDiscordBaseAddress = (uintptr_t)GetModuleHandleA("DiscordHook64.dll"); // Discord's dll name.

	return hDiscordBaseAddress;
}

bool discord::MH_CreateHook(LPVOID address, LPVOID targetFunction, LPVOID* returnFunction)
{
	auto hCreateHook = (0x136BD0 + hook->GetDiscordModuleAddress());
	if (!hCreateHook) return false;

	// This is using discord's minihooking function, so we can assume that the types would be LPVOID, LPVOID, and LPVOID* to hook functions.
	auto MH_CreateHook = reinterpret_cast<uintptr_t(__fastcall*)(LPVOID address, LPVOID targetFunction, LPVOID * returnFunction)>(hCreateHook);

	return MH_CreateHook(address, targetFunction, returnFunction) == MH_OK ? true : false;
}

bool discord::MH_QueueEnableHook(LPVOID address)
{
	auto hQueueEnableHook = (0x1376E0 + hook->GetDiscordModuleAddress());
	if (!hQueueEnableHook) return false;

	auto MH_QueueEnableHook = reinterpret_cast<uintptr_t(__fastcall*)(LPVOID address, bool bResult)>(hQueueEnableHook);

	// We can check if the operation completed as intended by checking if the return = MH_OK, or 0, because thats how MiniHook operates. 

	return MH_QueueEnableHook(address, true) == MH_OK ? true : false;
}

bool discord::MH_QueueDisableHook(LPVOID address)
{
	auto hQueueEnableHook = (0x1376E0 + hook->GetDiscordModuleAddress());
	if (!hQueueEnableHook) return false;

	auto MH_QueueEnableHook = reinterpret_cast<uintptr_t(__fastcall*)(LPVOID address, bool bResult)>(hQueueEnableHook);

	// We can check if the operation completed as intended by checking if the return = MH_OK, or 0, because thats how MiniHook operates. 

	return MH_QueueEnableHook(address, false) == MH_OK ? true : false;
}

bool discord::MH_ApplyQueued()
{
	auto hAppleQueued = (0x1369C0 + hook->GetDiscordModuleAddress());
	if (!hAppleQueued) return false;
	
	// Not a __fastcall function, so we call this as a __stdcall function to match its requirments.
	auto MH_AppleQueued = reinterpret_cast<uintptr_t(__stdcall*)()>(hAppleQueued);

	// We can check if the operation completed as intended by checking if the return = MH_OK, or 0, because thats how MiniHook operates. 

	return MH_AppleQueued() == MH_OK ? true : false;
}

bool discord::MH_HookFunction(LPVOID address, LPVOID targetFunction, LPVOID* returnFunction)
{
	// Just a function to combine it all into one to save time.
	if (MH_CreateHook(address, targetFunction, returnFunction))
	{
		if (MH_QueueEnableHook(address))
		{
			if (MH_ApplyQueued())
			{
				return true;
			}
		}
	}

	return false;
}