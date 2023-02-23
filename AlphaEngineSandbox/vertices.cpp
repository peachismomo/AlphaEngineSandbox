#pragma once
#include "AEEngine.h"
#include "vertices.h"
#include "helper.h"

namespace vertices {
	//void GetVertices(int type, vec3 dimensions, vec3 pos) {
	//	/*CUBOID*/
	//	if (type == 1) {
	//		/*XY-PLANE*/
	//		AEVec2 xyCoords[4]{};
	//		xyCoords[0] = AEVec2{ pos.x - dimensions.x / 2, pos.y + dimensions.y / 2 }; //top right
	//		xyCoords[1] = AEVec2{ pos.x + dimensions.x / 2, pos.y + dimensions.y / 2 }; //top left
	//		xyCoords[2] = AEVec2{ pos.x - dimensions.x / 2, pos.y - dimensions.y / 2 }; //bot right
	//		xyCoords[3] = AEVec2{ pos.x + dimensions.x / 2, pos.y - dimensions.y / 2 }; //bot left

	//		/*XZ-PLANE*/
	//		AEVec2 xzCoords[4]{};
	//		xzCoords[0] = AEVec2{ pos.x - dimensions.x / 2, pos.z + dimensions.z / 2 }; // top right
	//		xzCoords[1] = AEVec2{ pos.x + dimensions.x / 2, pos.z + dimensions.z / 2 }; // top left
	//		xzCoords[2] = AEVec2{ pos.x - dimensions.x / 2, pos.z - dimensions.z / 2 }; // bot right
	//		xzCoords[3] = AEVec2{ pos.x + dimensions.x / 2,  pos.z - dimensions.z / 2 }; // bot left

	//		/*YZ-PLANE*/
	//		AEVec2 yzCoords[4]{};
	//		yzCoords[0] = AEVec2{ pos.y - dimensions.y / 2, pos.x + dimensions.z / 2 }; //top right
	//		yzCoords[1] = AEVec2{ pos.y + dimensions.y / 2, pos.x + dimensions.z / 2 }; //top left
	//		yzCoords[2] = AEVec2{ pos.y - dimensions.y / 2, pos.x - dimensions.z / 2 }; //bot right
	//		yzCoords[3] = AEVec2{ pos.y + dimensions.y / 2, pos.x - dimensions.z / 2 }; //bot left
	//	}

	//	/*TRIANGLE PRISM*/
	//	else if (type == 2) {
	//		/*XY-PLANE*/
	//		/*
	//		* there is never rotation about the z axis, therefore the xy plane will always be a rectangle
	//		*/
	//		AEVec2 xyCoords[4]{};
	//		xyCoords[0] = AEVec2{ pos.x - dimensions.x / 2, pos.y + dimensions.y / 2 }; //top right
	//		xyCoords[1] = AEVec2{ pos.x + dimensions.x / 2, pos.y + dimensions.y / 2 }; //top left
	//		xyCoords[2] = AEVec2{ pos.x - dimensions.x / 2, pos.y - dimensions.y / 2 }; //bot right
	//		xyCoords[3] = AEVec2{ pos.x + dimensions.x / 2, pos.y - dimensions.y / 2 }; //bot left

	//		/*XZ-PLANE*/
	//		/*
	//		* By Default, the stair is facing the YZ plane, therefore, the triangle face is along the XZ plane.
	//		* If needed, rotations will be done later.
	//		*/
	//		AEVec2 xzCoords[3]{};
	//		xzCoords[0] = AEVec2{ pos.x - dimensions.x / 3,		 pos.z - dimensions.z / 3 }; // bot left
	//		xzCoords[1] = AEVec2{ pos.x - dimensions.x / 3,		 pos.z + (2 * dimensions.z) / 3 }; // top left
	//		xzCoords[2] = AEVec2{ pos.x + (2 * dimensions.x) / 3,  pos.z - dimensions.z / 3 }; // bot right

	//		/*YZ-PLANE*/
	//		/*
	//		* This might change to be a triangle if rotated
	//		*/
	//		AEVec2 yzCoords[4]{};
	//		yzCoords[0] = AEVec2{ pos.y - dimensions.y / 2, pos.x + dimensions.z / 2 }; //top right
	//		yzCoords[1] = AEVec2{ pos.y + dimensions.y / 2, pos.x + dimensions.z / 2 }; //top left
	//		yzCoords[2] = AEVec2{ pos.y - dimensions.y / 2, pos.x - dimensions.z / 2 }; //bot right
	//		yzCoords[3] = AEVec2{ pos.y + dimensions.y / 2, pos.x - dimensions.z / 2 }; //bot left
	//	}
	//}

	AEVec2* GetVerticesXY(helper::Object obj, int& count) {
		count = 4;
		AEVec2 xyCoords[4]{};
		xyCoords[0] = AEVec2{ obj.pos.x - obj.width / 2, obj.pos.y + obj.length / 2,}; //top right
		xyCoords[1] = AEVec2{ obj.pos.x + obj.width / 2, obj.pos.y + obj.length / 2 }; //top left
		xyCoords[2] = AEVec2{ obj.pos.x - obj.width / 2, obj.pos.y - obj.length / 2 }; //bot right
		xyCoords[3] = AEVec2{ obj.pos.x + obj.width / 2, obj.pos.y - obj.length / 2 }; //bot left
		return xyCoords;
	}

	AEVec2* GetVerticesYZ(helper::Object obj, int& count) {
		count = 4;
		AEVec2 yzCoords[4]{};
		yzCoords[0] = AEVec2{ obj.pos.y - obj.width / 2, obj.z + obj.height / 2 }; //top right
		yzCoords[1] = AEVec2{ obj.pos.y + obj.width / 2, obj.z + obj.height / 2 }; //top left
		yzCoords[2] = AEVec2{ obj.pos.y - obj.width / 2, obj.z - obj.height / 2 }; //bot right
		yzCoords[3] = AEVec2{ obj.pos.y + obj.width / 2, obj.z - obj.height / 2 }; //bot left
		return yzCoords;
	}

	AEVec2* GetVerticesXZ(helper::Object obj, int& count) {
		if (obj.type) {
			count = 4;
			AEVec2 xzCoords[4]{};
			xzCoords[0] = AEVec2{ obj.pos.x - obj.width / 2, obj.z + obj.height / 2 }; // top right
			xzCoords[1] = AEVec2{ obj.pos.x + obj.width / 2, obj.z + obj.height / 2 }; // top left
			xzCoords[2] = AEVec2{ obj.pos.x - obj.width / 2, obj.z - obj.height / 2 }; // bot right
			xzCoords[3] = AEVec2{ obj.pos.x + obj.width / 2, obj.z - obj.height / 2 }; // bot left
			return xzCoords;
		}
		else {
			count = 3;
			AEVec2 xzCoords[3]{};
			xzCoords[0] = AEVec2{	obj.pos.x - obj.width / 3,
									obj.z - obj.height / 3 };		// bot left

			xzCoords[1] = AEVec2{	obj.pos.x - obj.width / 3,
									obj.z + (2 * obj.height) / 3 }; // top left

			xzCoords[2] = AEVec2{	obj.pos.x + (2 * obj.width) / 3,
									obj.z - obj.height / 3 };		// bot right

			return xzCoords;
		}
	}
}