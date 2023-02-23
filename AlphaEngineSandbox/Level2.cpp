#include "AEEngine.h"
#include "GameObject.h"
#include "GSM.h"
#include "Enum.h"

using namespace GameObjects;
GameObject		playerObj;
Character		playerObjInst;

namespace Level2 
{
	void Level2_Load() {
		playerObj = GameObject(1, "C:/Users/Chua/source/repos/AlphaEngineSandbox/Assets/player.png");
	}

	void Level2_Init() {
		playerObjInst = Character(&playerObj, { 40.f, 80.f });
		playerObjInst.SetSprite(11, 8);
	}

	void Level2_Update() {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			GSM::next = Enum::GS_QUIT;

		playerObjInst.CheckInput();
		playerObjInst.Jump();
		playerObjInst.Animate();
		playerObjInst.Move();
		playerObjInst.Transform();
	}

	void Level2_Draw() {
		playerObjInst.Render(playerObjInst.GetSpriteOffset(), playerObjInst.GetSpriteDimensions());
	}

	void Level2_Free() {

	}

	void Level2_Unload() {
		AEGfxMeshFree(playerObj.GetMesh());
		AEGfxTextureUnload(playerObj.GetTexture());
	}
}