#pragma once
#include "AEEngine.h"
#include "Enum.h"

namespace helper {
	struct Vector {
		f32 x, y;
	};

	struct Object {
		AEGfxVertexList* pMesh;
		f32 width, height, rotation;
		Vector pos;
	};

	struct Wall {
		AEGfxTexture* pTex;
	};

	struct Floor {
		AEGfxTexture** pTex;
	};

	/*
	* AEGfxTexture** pTex
	* - Dynamic pointer to an array containing the sprites.
	*
	* Vector direction
	* - Vector direction of the player.
	*
	* f32 speed
	* - Unit speed of character.
	*
	* int state
	* - State of player. (MOVING, IDLE etc)
	*
	* int spriteX
	* - Number of columns.
	*
	* int spriteY
	* - Number of rows.
	*
	* int pTexOffsetX
	* - Texture offset x.
	*
	* int pTexOffsetY
	* - Texture offset y.
	*/
	struct Character {
		Object obj;
		AEGfxTexture* pTex;
		Vector direction;
		f32 speed;
		int state, spriteX, spriteY, spriteIteration, pTexOffsetX, pTexOffsetY;
	};

	void RenderObject(Character &character);
	bool direction(Character character, int a, int b);
	void setTextureOffsetY(Character& character);
	void setTextureOffsetX(Character& character);
	bool playerMovement(Character& player);
	f32 GetLength(Vector a);
	Vector vecNormalize(Vector a);
	Vector vecAdd(Vector a, Vector b);
	Vector vecScale(Vector a, f32 scale);
}

