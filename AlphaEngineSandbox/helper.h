#pragma once
#include "AEEngine.h"
#include "Enum.h"

namespace helper {
	struct Vector {
		f32 x, y;
	};

	struct Object {
		AEGfxVertexList* pMesh;
		f32 width, length, height, rotation;
		AEVec2 pos;
		f32 z;
		int type;
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
	struct CharStruct {
		Object obj;
		AEGfxTexture* pTex;
		AEVec2 direction;
		f32 speed;
		int state, spriteX, spriteY, spriteIteration, pTexOffsetX, pTexOffsetY;
	};

	void pressSpace(CharStruct& character);

	/*GAMEOBJECTS.CPP*/
	void renderPlayer(CharStruct &character);
	/*GAMEOBJECTS.CPP END*/

	/*ANIMATION.CPP*/
	bool direction(CharStruct character, int a, int b);
	void setTextureOffsetY(CharStruct& character);
	void setTextureOffsetX(CharStruct& character);
	bool playerMovement(CharStruct& player);
	/*ANIMATION.CPP END*/

	void RenderObject(Object obj);
	AEVec2* GetVertices(const Object obj);
	bool SAT_Collision(Object obj1, Object obj2, f32& depth, AEVec2& normal);
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len);
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal);
}

