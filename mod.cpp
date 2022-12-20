#include "pch.h"
#include "frontiers-lua-extensions/ScriptSequenceExtras.h"

extern "C"
{
	void __declspec(dllexport) __cdecl Init()
	{
		frontiers_lua_extensions::ScriptSequenceExtras::InstallHooks();
	}
}
