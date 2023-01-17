// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include <math.h>



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here
	double coords[8][2] = {
		{ -0.5f / 5, -0.5f / 5 },
		{ -0.5f / 5, 0.5f / 5 },
		{ 0.5f / 5, 0.5f / 5 },
		{ 0.5f / 5, -0.5f / 5 },
		{ -0.5f / 10, -0.5f / 10 },
		{ -0.5f / 10, 0.5f / 10},
		{ 0.5f / 10, 0.5f / 10 },
		{ 0.5f / 10, -0.5f / 10 }
	};

	for (int i = 0; i < 8; i++)
	{
		coords[i][0] = coords[i][0] * cos(90) - coords[i][1] * sin(90);
		coords[i][1] = coords[i][0] * sin(90) + coords[i][1] * cos(90);
	}
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("Alpha Engine sandbox");

	// reset the system modules
	AESysReset();

	// Pointer to Mesh
	AEGfxVertexList* pMesh = 0;
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();
	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB
	// UV coordinates to read from loaded textures

	AEGfxTriAdd(
		coords[0][0], coords[0][1], 0xFFFF00FF, 0.0f, 0.0f,
		coords[1][0], coords[1][1], 0xFFFFFF00, 0.0f, 1.0f,
		coords[2][0], coords[2][1], 0xFF00FFFF, 0.0f, 2.0f);
	AEGfxTriAdd(
		coords[0][0], coords[0][1], 0xFFFFFFFF, 1.0f, 0.0f,
		coords[2][0], coords[2][1], 0xFFFFFFFF, 1.0f, 1.0f,
		coords[3][0], coords[3][1], 0xFFFFFFFF, 1.0f, 2.0f);

	AEGfxTriAdd(
		coords[4][0], coords[4][1], 0xFFFF00FF, 0.0f, 0.0f,
		coords[5][0], coords[5][1], 0xFFFFFF00, 0.0f, 1.0f,
		coords[6][0], coords[6][1], 0xFF00FFFF, 0.0f, 2.0f);
	AEGfxTriAdd(
		coords[4][0], coords[4][1], 0xFFFFFFFF, 1.0f, 0.0f,
		coords[6][0], coords[6][1], 0xFFFFFFFF, 1.0f, 1.0f,
		coords[7][0], coords[7][1], 0xFFFFFFFF, 1.0f, 2.0f);


	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/ffffff.png");

	//delta time increments
	double planetRotInc = 120.f * AEFrameRateControllerGetFrameTime();
	double posRotInc = AEFrameRateControllerGetFrameTime();

	//initial rotations
	double planetRotation = planetRotInc;
	double positionRotation = 360;

	//inital position
	double translateX = 0.f, translateY = 0.f;
	f32 pTransform[4][4]{ 0 };
	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Your own update logic goes here

		// Your own rendering logic goes here
		//AEGfxSetTransform3D(pTransform);
		//// Set the background to black.
		//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		//// Tell the engine to get ready to draw something with texture.
		//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		//// Set the tint to white, so that the sprite can
		//// display the full range of colors (default is black).
		//AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		//// Set blend mode to AE_GFX_BM_BLEND
		//// This will allow transparency.
		//AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		//AEGfxSetTransparency(1.0f);
		//// Set the texture to pTex
		//AEGfxTextureSet(pTex, 0, 0);
		//// Create a scale matrix that scales by 100 x and y
		//AEMtx33 scale = { 0 };
		//AEMtx33Scale(&scale, 1000.f, 1000.f);
		//// Create a rotation matrix that rotates by 45 degrees
		//double rotationPi = 45 * PI;
		//AEMtx33 rotate = { 0 };
		//AEMtx33Rot(&rotate, rotationPi);
		////change in rotation
		planetRotation = planetRotation < 360 ? planetRotation + planetRotInc : planetRotInc;
		//// Create a translation matrix that translates by
		//// 100 in the x-axis and 100 in the y-axis
		//AEMtx33 translate = { 0 };

		////rotation about the origin
		//double pointX = cos(positionRotation) * translateX + (-sin(positionRotation) * translateY);
		//double pointY = sin(positionRotation) * translateX + cos(positionRotation) * translateY;
		//AEMtx33Trans(&translate, pointX, pointY);

		////change in rotation
		//positionRotation = positionRotation > 0 ? positionRotation - posRotInc : 360;

		//// Concat the matrices (TRS)
		//AEMtx33 transform = { 0 };
		//AEMtx33Concat(&transform, &rotate, &scale);
		//AEMtx33Concat(&transform, &translate, &transform);
		//// Choose the transform to use
		//AEGfxSetTransform(transform.m);
		// 
		// Set the background to black.
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// Set the tint to white, so that the sprite can 
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		// Set the texture to pTex
		AEGfxTextureSet(pTex, 0, 0);

		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, 1000.f, 1000.f);

		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate;
		AEVec2 vec1;
		vec1.x = cos(planetRotation), vec1.y = -sin(planetRotation);
		AEVec2 vec2;
		vec2.x = sin(planetRotation), vec2.y = cos(planetRotation);
		AEVec2 vec3;
		vec3.x = 0, vec3.y = 0;
		AEMtx33SetRow(&rotate, 0, &vec1);
		AEMtx33SetRow(&rotate, 0, &vec2);
		AEMtx33SetRow(&rotate, 0, &vec3);

		//AEMtx33Rot(&rotate, PI);
		//{ {cos(planetRotation), -sin(planetRotation), 0}, { sin(planetRotation), cos(planetRotation), 0 }, { 0,0,1 } };
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, 100.f, 100.f);

		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);

		// Choose the transform to use
		AEGfxSetTransform(transform.m);

		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxTextureUnload(pTex);
	AEGfxMeshFree(pMesh);
	// free the system
	AESysExit();
}