#include "GSM.h"
#include "Enum.h"
#include "Level1.h"
#include "AEEngine.h"

namespace GSM {
	int current, previous, next;
	f64 gameTime;
	FP fpLoad = nullptr, fpInit = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

	void GSM_Init(int start) {
		current = previous = next = start;
		gameTime = 0.f;
	}

	void GSM_Update() {
		using namespace Enum;
		switch (current) {
		case GS_QUIT:
			break;
		case GS_LEVEL1:
			fpLoad = Level1::Level1_Load;
			fpInit = Level1::Level1_Init;
			fpUpdate = Level1::Level1_Update;
			fpDraw = Level1::Level1_Draw;
			fpFree = Level1::Level1_Free;
			fpUnload = Level1::Level1_Unload;
			break;
		case GS_RESTART:
			break;
		}
	}
}

