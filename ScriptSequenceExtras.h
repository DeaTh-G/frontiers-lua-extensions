#pragma once

namespace frontiers_lua_extensions
{
	class ScriptSequenceExtras : public app::ScriptSequence
	{
	public:
		static void InstallHooks();

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