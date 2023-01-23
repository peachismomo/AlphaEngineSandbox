#pragma once
#include "AEEngine.h"
namespace GSM
{
	typedef void(*FP)(void);

	extern int current, previous, next;
	extern f64 gameTime;
	extern FP fpLoad, fpInit, fpUpdate, fpDraw, fpFree, fpUnload;

	void GSM_Init(int startingState);
	void GSM_Update();
}

