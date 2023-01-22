#include "Level1.h"
#include "AEEngine.h"
#include "helper.h"
#include "GSM.h"

namespace Level1 {
	using namespace helper;
	using namespace GSM;

	Character player;
	s8 fontId;
	void Level1_Load() {
		AE_ASSERT_MESG(player.pTex = AEGfxTextureLoad("C:/Users/Chua/source/repos/AlphaEngineSandbox/Assets/player.png"), "Failed to load texture");
		AE_ASSERT_MESG(fontId = AEGfxCreateFont("C:/Users/Chua/source/repos/AlphaEngineSandbox/Assets/Roboto-Regular.ttf", 12), "Failed to load font");
	}

	void Level1_Init() {
		/*CREATE PLAYER*/
		player.obj.width = 30, player.obj.height = 30, player.obj.rotation = 0, player.obj.pos.x = 100, player.obj.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f / 8.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 11.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.obj.pMesh = AEGfxMeshEnd();
		player.direction = Vector{ 0,0 }, player.speed = 100.0f;
		player.spriteX = 11, player.spriteY = 8, player.spriteIteration = 0;
		player.pTexOffsetX = 0, player.pTexOffsetY = 0;
		player.state = 0;
	}

	void Level1_Update() {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			next = Enum::GS_QUIT;

		bool isMoving{ playerMovement(player) };
		/*UPDATE LOGIC*/
		if (isMoving) {
			player.state = 1;
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			player.direction = vecNormalize(player.direction);
			player.obj.pos = vecAdd(player.obj.pos, vecScale(player.direction, unitSpeed));
		}
		else {
			player.state = 0;
		}
	}

	void Level1_Draw() {
		RenderObject(player);
		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "SpriteIteration: %d", player.spriteIteration);

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(fontId, strBuffer, static_cast<f32>(-0.95), static_cast<f32>(-0.95), static_cast <f32>(1.0f), static_cast <f32>(1.f), static_cast <f32>(1.f), static_cast <f32>(1.f));
	}

	void Level1_Free() {
		AEGfxMeshFree(player.obj.pMesh);
	}

	void Level1_Unload() {
		AEGfxTextureUnload(player.pTex);
		AEGfxDestroyFont(fontId);
	}
}