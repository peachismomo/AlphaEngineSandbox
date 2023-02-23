#pragma once
#include "AEEngine.h"
#include "helper.h"

namespace vertices {
	struct vec3 {
		float x, y, z;
	};

	void GetVertices(int type, vec3 dimensions, vec3 pos);
	AEVec2* GetVerticesXY(helper::Object obj, int& count);
	AEVec2* GetVerticesYZ(helper::Object obj, int& count);
	AEVec2* GetVerticesXZ(helper::Object obj, int& count);
}