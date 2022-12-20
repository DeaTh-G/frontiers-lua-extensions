#include "pch.h"
#include "ScriptSequenceExtras.h"

typedef void (app::ScriptSequence::* SequenceFuncPtr)(lua_State*);

/* v1.10: 0x14087EF20 */
HOOK(void, __fastcall, RegisterLuaCallbacks, frontiers_lua_extensions::ScriptSequenceExtras::ms_addrRegisterLuaCallbacks, app::ScriptSequence* in_pThis, app::game::Script* in_pScript)
{
	originalRegisterLuaCallbacks(in_pThis, in_pScript);
	auto* luaWrapper = in_pScript->GetLuaWrapper();

	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&frontiers_lua_extensions::ScriptSequenceExtras::ShowTalkCaptionNoPrompt)>();
	luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&frontiers_lua_extensions::ScriptSequenceExtras::RobChaosEmerald)>();
}

void frontiers_lua_extensions::ScriptSequenceExtras::InstallHooks()
{
	INSTALL_HOOK(RegisterLuaCallbacks);
}