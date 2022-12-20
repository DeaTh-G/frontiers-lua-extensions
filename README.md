# frontiers-lua-extensions
A (currently very rudamentary mod that adds more lua functions to the game.

## Contribution
Contributing to the mod is fairly simple if you know C++.
Once you've downloaded the C++ project and loaded it up into Visual Studio 2022. 
1. You must define your new function in [ScriptSequenceExtras.h](/frontiers-lua-extensions/ScriptSequenceExtras.h)
2. Your new function must get added to the `RegisterLuaCallbacks` in [ScriptSequenceExtras.cpp](/frontiers-lua-extensions/ScriptSequenceExtras.cpp)\
in the same that the already existing ones are.\
Example: `luaWrapper->RegisterLuaCallback<static_cast<SequenceFuncPtr>(&frontiers_lua_extensions::ScriptSequenceExtras::RobChaosEmerald)>();`
3. Any new functions that require changing [rangers-api](https://github.com/DeaTh-G/rangers-api) must first make their changes as PR to that.
4. Coding style of the project must be followed.

## Approval and release process
Shortly after your PR getting accepted your GitHub username will be added to the credits of the mod and a new DLL will be released with your changes included.\
An update will be automically delivered to already released versions of this library mod and then people from all around the world will be able to use the newly exposed C++ function in lua.
