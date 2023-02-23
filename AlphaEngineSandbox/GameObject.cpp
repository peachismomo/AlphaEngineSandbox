#include "GameObject.h"
#include "helper.h"
#include "GSM.h"
#include <iostream>


const f32 PLAYER_SPEED = 150.f;
const f32 GRAVITY = -1000.f;

namespace
{
	bool chkDir(AEVec2 direction, int a, int b) {
		int x = static_cast<int>(direction.x);
		int y = static_cast<int>(direction.y);
		return (x == a && y == b);
	}
}

namespace GameObjects {
	GameObject::GameObject() {}

	GameObject::GameObject(unsigned long objType, const s8* fileName)
	{
		type = objType;

		pTex = AEGfxTextureLoad(fileName);
		AE_ASSERT_MESG(pTex, "Failed to load texture.");

		AEGfxMeshStart();
		if (type) {
			AEGfxTriAdd(
				-0.5f, -0.5f, 0xFFFF0000, .0f, .125f,
				0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, .125f,
				-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
			);
			AEGfxTriAdd(
				0.5f, 0.5f, 0xFFFF0000, 1.0f / 11.0f, .0f,
				0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, .125f,
				-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
			);
		}
		else {
			AEGfxTriAdd(
				-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
				0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
				-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
			);
			AEGfxTriAdd(
				0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
				0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
				-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
			);
		}

		pMesh = AEGfxMeshEnd();
	}

	GameObject::~GameObject()
	{
		/*AEGfxMeshFree(pMesh);
		AEGfxTextureUnload(pTex);*/
	}

	AEGfxTexture* GameObject::GetTexture() const
	{
		return pTex;
	}

	AEGfxVertexList* GameObject::GetMesh() const
	{
		return pMesh;
	}

	GameObjInst::GameObjInst() {}

	GameObjInst::GameObjInst(GameObject* pGameObject, AEVec2 initScale, AEVec2 initPos, f32 initElevation)
	{
		pObject = pGameObject;
		flag = 0;
		scale = initScale;
		pos = initPos;
		elevation = initElevation;
		transform = { 0 };
	}

	GameObjInst::~GameObjInst()
	{

	}

	AEVec2 GameObjInst::ConvertIsometric()
	{
		return { pos.x + pos.y,
			-0.5f * pos.x + 0.5f * pos.y };
	}

	void GameObjInst::Render(AEVec2 offset, AEVec2 spriteDimensions)
	{
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		AEGfxTextureSet(pObject->GetTexture(), offset.x / spriteDimensions.x, offset.y / spriteDimensions.y);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pObject->GetMesh(), AE_GFX_MDM_TRIANGLES);
	}

	void GameObjInst::Transform()
	{
		/*TRANSFORMATION*/
		AEMtx33	transTRS{ 0 }, rotTRS{ 0 }, scaleTRS{ 0 };
		AEVec2 isoCoords = this->ConvertIsometric();

		/*TRANSFORMATION MATRIX (TRS)*/
		AEMtx33Scale(&scaleTRS, scale.x, scale.y);
		AEMtx33Rot(&rotTRS, 0.f);
		AEMtx33Trans(&transTRS, isoCoords.x, isoCoords.y + elevation);
		AEMtx33Concat(&transform, &rotTRS, &scaleTRS);
		AEMtx33Concat(&transform, &transTRS, &transform);
	}

	AEVec2* GameObjInst::GetPosition()
	{
		return &this->pos;
	}

	f32* GameObjInst::GetElevation()
	{
		return &this->elevation;
	}

	Character::Character() {}

	Character::Character(GameObject* pGameObject, AEVec2 initScale, AEVec2 initPos, f32 initElevation)
		: GameObjInst(pGameObject, initScale, initPos, initElevation)
	{
		isMoving = false;
		spriteDimensions = { 0 };
		spriteOffset = { 0 };
		yVel = 0;
		yAccel = 0;
		direction = { 0 };
		spriteIter = 0;
	}

	Character::~Character()
	{

	}

	void Character::SetSprite(unsigned int width, unsigned int height)
	{
		spriteDimensions.x = width;
		spriteDimensions.y = height;
	}

	void Character::CheckInput()
	{
		if (!isJumping) {
			AEVec2 dirInput{ 0 };
			if (AEInputCheckCurr(AEVK_A)) {
				dirInput.x--;
			}
			if (AEInputCheckCurr(AEVK_D)) {
				dirInput.x++;
			}
			if (AEInputCheckCurr(AEVK_W)) {
				dirInput.y++;
			}
			if (AEInputCheckCurr(AEVK_S)) {
				dirInput.y--;
			}
			isMoving = dirInput.x || dirInput.y;
			direction = dirInput;
		}
	}

	void Character::Jump()
	{
		f32* y = GetElevation();

		yVel = GRAVITY * AEFrameRateControllerGetFrameTime() + yVel;

		if (AEInputCheckTriggered(AEVK_SPACE) && *y == 0) {
			yVel = sqrt(2 * -GRAVITY * (50.f));
		}

		//*y = yVel > 0 ? yVel * AEFrameRateControllerGetFrameTime() + *y : *y;
		*y = yVel * AEFrameRateControllerGetFrameTime() + *y;
		if (*y < 0)
			*y = 0;
		isJumping = *y;
	}

	void Character::Move()
	{
		AEVec2* currPos = GetPosition();
		AEVec2 initialPos = *currPos;
		if (isMoving)
		{
			f32 unitSpeed = PLAYER_SPEED * AEFrameRateControllerGetFrameTime();

			AEVec2Normalize(&direction, &direction);
			AEVec2Scale(&direction, &direction, unitSpeed);
			AEVec2Add(currPos, currPos, &direction);
		}

		if (CheckBoundary(*currPos))
		{
			*currPos = initialPos;
		}
	}

	bool Character::CheckBoundary(AEVec2 position)
	{
		AEVec2 boarderMin = { -9.f * 20.f, -9.f * 20.f };
		AEVec2 boarderMax = { 9.f * 20.f, 9.f * 20.f };

		if (
			boarderMin.x < position.x && position.x < boarderMax.x &&
			boarderMin.y < position.y && position.y < boarderMax.y
			)
			return false;
		else return true;
	}

	void Character::Animate()
	{
		/*SET SPRITE Y OFFSET*/
		if (chkDir(direction, 1, 1)) {
			spriteOffset.y = 1;
		}
		else if (chkDir(direction, 1, 0)) {
			spriteOffset.y = 2;
		}
		else if (chkDir(direction, 1, -1)) {
			spriteOffset.y = 3;
		}
		else if (chkDir(direction, 0, -1)) {
			spriteOffset.y = 4;
		}
		else if (chkDir(direction, -1, -1)) {
			spriteOffset.y = 5;
		}
		else if (chkDir(direction, -1, 0)) {
			spriteOffset.y = 6;
		}
		else if (chkDir(direction, -1, 1)) {
			spriteOffset.y = 7;
		}
		else if (chkDir(direction, 0, 1)) {
			spriteOffset.y = 0;
		}

		/*SET SPRITE X OFFSET*/
		if (isJumping) {
			spriteOffset.x = 4;
		}

		else if (isMoving)
		{
			if (GSM::gameTime >= 0.08f)
			{
				spriteIter++;
				spriteIter %= ((int)spriteDimensions.x - 1);
				GSM::gameTime = 0.f;
			}
			spriteOffset.x = spriteIter + 1;
		}

		else {
			spriteOffset.x = 0;
		}
	}

	AEVec2 Character::GetSpriteOffset() const
	{
		return spriteOffset;
	}

	AEVec2 Character::GetSpriteDimensions() const
	{
		return spriteDimensions;
	}
}