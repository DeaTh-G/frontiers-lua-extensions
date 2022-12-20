#pragma once

namespace frontiers_lua_extensions
{
	class ScriptSequenceExtras : public app::ScriptSequence
	{
	public:
		inline static void* ms_addrRegisterLuaCallbacks = sigScan("\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x20\x48\x8B\xF9\x48\x8B\xCA", "xxxxxxxxxxxxxxxxxxxxx", (void*)0x14087EF20);
		static void InstallHooks();

		/// <summary>
		/// Triggers a caption and the voice line for it that doesn't require player input to proceed.
		/// </summary>
		/// <param name="lua usage:">ShowTalkCaptionNoPrompt(string)</param>
		/// <param name="string:">ID of the caption text and voice line to trigger.</param>
		void ShowTalkCaptionNoPrompt(lua_State* in_pLuaState)
		{
			app::GameDocument* pDocument = GetDocument();

			const char* pCaptionName = lua_tolstring(in_pLuaState, 1, 0);
			if (pCaptionName)
			{
				void* pOverlayMem = pDocument->pAllocator->Alloc(sizeof(app::ui::RequestOverlayCaption), 8);
				app::ui::RequestOverlayCaption* pOverlay = new(pOverlayMem) app::ui::RequestOverlayCaption();

				pOverlay->SetupCaptionInfo(pCaptionName, pCaptionName, 0.3f);
				pOverlay->Unk3 = 1;
				pOverlay->Type = 5;
				pOverlay->Unk11 = 16;

				auto* pOverlayService = pDocument->GetService<app::ui::UIOverlayService>();
				int jobCount = pOverlayService->CreateOverlayJob(pOverlay);

				SetCaptionType(jobCount);
				PlayLipAnimation(pCaptionName);
			}
			lua_yieldk(in_pLuaState, 0, 0, 0);
		}

		/// <summary>
		/// Takes away the specified Chaos Emerald from the player.
		/// </summary>
		/// <param name="lua usage:">RobChaosEmerald(string)</param>
		/// <param name="string:">Name of the Chaos Emerald.</param>
		void RobChaosEmerald(lua_State* in_pLuaState)
		{
			char emeraldType{};
			app::GameDocument* pDocument = GetDocument();

			const char* pEmeraldName = lua_tolstring(in_pLuaState, 1, 0);
			switch (csl::ut::StringMapOperation::hash(pEmeraldName))
			{
			case 0x1FA47A:			emeraldType = 0; break;			// Blue
			case 0x20487E70:		emeraldType = 1; break;			// LightBlue
			case 0x41DDEE3:			emeraldType = 2; break;			// Green
			case 0xF29F3DC:			emeraldType = 3; break;			// Purple
			case 0x14071:			emeraldType = 4; break;			// Red
			case 0x4FADC09:			emeraldType = 5; break;			// White
			case 0x1DA15094:		emeraldType = 6; break;			// Yellow
			}

			app::MsgRobChaosEmerald msgRobEmerald{ emeraldType };
			SendMessageImmToPlayer(pDocument, 0, msgRobEmerald);
		}
	};
}