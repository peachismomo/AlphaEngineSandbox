#include <math.h>

namespace graphicalMaths {
	/*
	* aspect => h / w
	*/
	void make_perspective(double matrix[4][4], double fov, double aspect, double znear, double zfar) {
		matrix = { 0 };
		matrix[0][0] = aspect * (1 / tan(fov / 2));
		matrix[1][1] = (1 / tan(fov / 2));
		matrix[2][2] = zfar / (zfar - znear);
		matrix[2][3] = (-zfar * znear) / (zfar - znear);
		matrix[3][2] = 1.f;
	}

	void matrixMultiply(double projMat[4][4], double coords[4]) {
		for (int i = 0; i < 4; i++) {
			for (int x = 0; x < 4; x++) {
				projMat[x][i] * coords[i];
			}
		}
	}
}