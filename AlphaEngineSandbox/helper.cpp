#include "helper.h"

namespace helper {
	void RenderObject(Character &character) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		/*Set texture*/
		setTextureOffsetX(character);
		setTextureOffsetY(character);
		AEGfxTextureSet(character.pTex,
			static_cast<f32>(character.pTexOffsetX) / static_cast<f32>(character.spriteX),
			static_cast<f32>(character.pTexOffsetY) / static_cast<f32>(character.spriteY));

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, AEDegToRad(character.obj.rotation));

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, character.obj.width, character.obj.height);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, character.obj.pos.x, character.obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(character.obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	bool direction(Character character, int a, int b) {
		int x = round(character.direction.x);
		int y = round(character.direction.y);
		return (x == a && y == b);
	}

	void setTextureOffsetY(Character& character) {
		if (direction(character, 1, 1)) {
			character.pTexOffsetY = 0;
		}
		else if (direction(character, 1, 0)) {
			character.pTexOffsetY = 1;
		}
		else if (direction(character, 1, -1)) {
			character.pTexOffsetY = 2;
		}
		else if (direction(character, 0, -1)) {
			character.pTexOffsetY = 3;
		}
		else if (direction(character, -1, -1)) {
			character.pTexOffsetY = 4;
		}
		else if (direction(character, -1, 0)) {
			character.pTexOffsetY = 5;
		}
		else if (direction(character, -1, 1)) {
			character.pTexOffsetY = 6;
		}
		else if (direction(character, 0, 1)) {
			character.pTexOffsetY = 7;
		}
	}

	void setTextureOffsetX(Character& character) {
		if (character.state) {
			if (!(AEFrameRateControllerGetFrameCount() % 6)) {
				character.spriteIteration++;
				character.spriteIteration %= (character.spriteX - 1);
			}
			character.pTexOffsetX = character.spriteIteration;
		}
		else {
			character.pTexOffsetX = 0;
		}
	}

	bool playerMovement(Character& player) {
		Vector dir = Vector{ 0,0 };
		if (AEInputCheckCurr(AEVK_A)) {
			dir.x--;
		}
		if (AEInputCheckCurr(AEVK_D)) {
			dir.x++;
		}
		if (AEInputCheckCurr(AEVK_W)) {
			dir.y++;
		}
		if (AEInputCheckCurr(AEVK_S)) {
			dir.y--;
		}
		player.direction = dir;
		return !(dir.x == 0 && dir.y == 0);
	}

	f32 GetLength(Vector a) {
		return sqrt(pow(a.x, 2) + pow(a.y, 2));
	}

	Vector vecNormalize(Vector a) {
		f32 len = GetLength(a);
		return Vector{ a.x / len, a.y / len };
	}

	Vector vecAdd(Vector a, Vector b) {
		return Vector{ a.x + b.x, a.y + b.y };
	}

	Vector vecScale(Vector a, f32 scale) {
		return Vector{ a.x *= scale, a.y * scale };
	}
}