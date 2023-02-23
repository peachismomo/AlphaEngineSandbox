#include "helper.h"
#include "GSM.h"
#include <limits>

namespace helper {
	void renderPlayer(CharStruct& character) {
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
		AEMtx33Trans(&translate, (character.obj.pos.x - character.obj.z) / sqrt(2), (character.obj.pos.x + 2 * character.obj.pos.y + character.obj.z) / sqrt(8));

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(character.obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	bool direction(CharStruct character, int a, int b) {
		int x = static_cast<int>(character.direction.x);
		int y = static_cast<int>(character.direction.y);
		return (x == a && y == b);
	}

	void setTextureOffsetY(CharStruct& character) {
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

	void setTextureOffsetX(CharStruct& character) {
		if (character.state) {
			if (GSM::gameTime >= 0.08f) {
				character.spriteIteration++;
				character.spriteIteration %= (character.spriteX - 1);
				GSM::gameTime = 0.f;
			}
			character.pTexOffsetX = character.spriteIteration + 1;
		}
		else {
			character.pTexOffsetX = 0;
		}
	}

	bool playerMovement(CharStruct& player) {
		AEVec2 dir = AEVec2{ 0.f,0.f };
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
		//player.direction.x = dir.x + dir.y;
		//player.direction.y = -0.5f * dir.x + 0.5f * dir.y;
		player.direction = dir;
		return !(dir.x == 0 && dir.y == 0);
	}

	/*SAT COLLISION*/
	bool SAT_Collision(Object obj1, Object obj2, f32& depth, AEVec2& normal, AEVec2* (*callback)(Object, int&)) {
		/*Number of vertices*/
		int lenA = 0;/**(&verticesA + 1) - verticesA;*/
		int lenB = 0;/**(&verticesB + 1) - verticesB;*/

		/*Get vertices of the 2 objects*/
		AEVec2* verticesA = callback(obj1, lenA);
		AEVec2* verticesB = callback(obj2, lenB);

		/*Initialize/reset normal and depth*/
		normal = AEVec2{ 0,0 };
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		/*Check for all intersections*/
		bool out = (CheckIntersect(verticesA, verticesB, lenA, lenB, depth, normal) && CheckIntersect(verticesB, verticesA, lenB, lenA, depth, normal));

		depth /= AEVec2Length(&normal);
		AEVec2Normalize(&normal, &normal);

		/*Check if normal is pointing in the correct
		direction by comparing with center of object A to center of object B.*/

		AEVec2 dir = AEVec2{ obj2.pos.x - obj1.pos.x, obj2.pos.y - obj1.pos.y }; // Get vector from object A to object B

		/*If the normal is in the opposite direction, negate the vector.*/
		if (AEVec2DotProduct(&dir, &normal) < 0.f) {
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;

		return out;
	}

	AEVec2* GetVertices(const Object obj) {
		AEVec2* vertices = { new AEVec2[4] };
		AEVec2 original[4] = {
			AEVec2{ obj.pos.x - obj.width / 2, obj.pos.y + obj.height / 2 },
			AEVec2{ obj.pos.x + obj.width / 2, obj.pos.y + obj.height / 2 },
			AEVec2{ obj.pos.x + obj.width / 2, obj.pos.y - obj.height / 2 },
			AEVec2{ obj.pos.x - obj.width / 2, obj.pos.y - obj.height / 2 }
		};

		/* Get vertex after rotation. Vertex rotates around the center of the mesh */
		for (int i = 0; i < 4; i++) {
			f32 posX = original[i].x - obj.pos.x;
			f32 posY = original[i].y - obj.pos.y;
			vertices[i].x = posX * static_cast<f32>(AECosDeg(obj.rotation)) - posY * static_cast<f32>(AESinDeg(obj.rotation)) + obj.pos.x;
			vertices[i].y = posX * static_cast<f32>(AESinDeg(obj.rotation)) + posY * static_cast<f32>(AECosDeg(obj.rotation)) + obj.pos.y;
		}

		return vertices;
	}

	/*Projects the vertex onto a axis and returns the maximum and mimum points.*/
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len) {
		min = static_cast<f32>((std::numeric_limits<float>::max)());
		max = static_cast<f32>((std::numeric_limits<float>::min)());

		/*Get projection for each vertex and sets min and max respectively.*/
		for (int i = 0; i < len; i++) {
			f32 projection = AEVec2DotProduct(&vertices[i], &axis);
			min = projection < min ? projection : min;
			max = projection > max ? projection : max;
		}
	}

	/*Check if the maximum and minimum projections of each object intersects*/
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal) {
		for (int i = 0; i < lenA; i++) {
			f32 minA, maxA, minB, maxB;
			AEVec2 va = verticesA[i];
			AEVec2 vb = verticesA[(i + 1) % lenA]; // Loops back to the start if i reaches the end of the loop.

			AEVec2 edge;
			AEVec2Sub(&edge, &vb, &va); // Get edge created by the 2 vertex
			AEVec2 axis{ -edge.y, edge.x }; // Normal to the edge. Use this as the axis to compare to.

			/*Get minumum and maximum points*/
			ProjectVertices(verticesA, axis, minA, maxA, lenA);
			ProjectVertices(verticesB, axis, minB, maxB, lenB);

			/*If they do not intersect, return false.*/
			if (minA >= maxB || minB >= maxA)
				return false;

			f32 axisDepth = maxB - minA < maxA - minB ? maxB - minA : maxA - minB; // Length/depth of intersection

			/*Outs the smallest depth and axis for resolution*/
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}
		return true;
	}

	void RenderObject(Object obj) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTintColor(1.0f, 1.f, 1.f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, AEDegToRad(obj.rotation));

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height / 2.f);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	void pressSpace(CharStruct& character) {
		if (AEInputCheckCurr(AEVK_SPACE)) {
			character.obj.z++;
		}
	}
}