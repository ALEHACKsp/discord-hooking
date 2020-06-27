#pragma once
#include "stdafx.h"

discord* hDiscord;

HRESULT(*Present)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
ID3D11RenderTargetView* targetview = nullptr;

HRESULT __stdcall PresentScene(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{

    printf("\nx64 hook applied on discord's present scene function!");

    return Present(swapChain, syncInterval, flags);
}

bool Initialize()
{
    auto hPresentScene = (0x6B1A0 + hDiscord->GetDiscordModuleAddress());
    if (!hPresentScene) return false;
    hDiscord->MH_HookFunction((LPVOID)hPresentScene, PresentScene, (LPVOID*)&Present);
    // This wouldn't be considered undetected going against commercial-anticheats like BattleEye/EasyAntiCheat, but you can bypass this the lazy way
    // By using a RWX dll (Read/Write/Execute) that you can casually inject and load your dll off of.

    return true;
}

bool __stdcall dllmain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) 
    {
        if (Initialize())
        {
            
            return true;
        }
        else {
            MessageBoxA(0, "Failed to initialize!", "discord hooking", 0);
            return false;
        }
    }
    return false;
}