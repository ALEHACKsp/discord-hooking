#pragma once
#include "stdafx.h"

class discord
{
public:
	uintptr_t GetDiscordModuleAddress();
	bool MH_CreateHook(LPVOID address, LPVOID targetFunction, LPVOID* returnFunction);
	bool MH_QueueEnableHook(LPVOID address);
	bool MH_QueueDisableHook(LPVOID address);
	bool MH_ApplyQueued();
	bool MH_HookFunction(LPVOID address, LPVOID targetFunction, LPVOID* returnFunction);
};
