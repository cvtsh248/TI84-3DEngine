/*
 *--------------------------------------
 * Program Name:Simple 3D Engine
 * Author:Shourjo Chakravarty
 * License:
 * Description:
 *--------------------------------------
*/

#include <tice.h>
#include <math.h>
#include <stdlib.h>
#include <graphx.h>

#define FOV 70


//Vector implementation 
struct Vector{
	float x;
	float y;
	float z;
};

struct Vector4D{
	float x;
	float y;
	float z;
	float w;
};

struct Vector vecAdd(struct Vector *a, struct Vector *b){
	struct Vector ret;
	ret.x = b->x + a->x;
	ret.y = b->y + a->y;
	ret.z = b->z + a->z;
	return ret;
}

struct Vector vecSubtract(struct Vector *a, struct Vector *b){
	struct Vector ret;
	ret.x = a->x - b->x;
	ret.y = a->y - b->y;
	ret.z = a->z - b->z;
	return ret;
}

struct Vector vecScalarProduct(struct Vector *a, float b){
	struct Vector ret;
	ret.x = a->x * b;
	ret.y = a->y * b;
	ret.z = a->z * b;
	return ret;
}

struct Vector vecCrossProduct(struct Vector *a, struct Vector *b){
	struct Vector ret;
	ret.x = a->y * b->z - b->y * a->z;
	ret.y = a->z * b->x - b->z * a->x;
	ret.z = a->x * b->y - b->x * a->y;
	return ret;
}

float vecDotProduct(struct Vector *a, struct Vector *b){
	float ret = a->x * b->x + a->y * b->y + a->z * b-> z;
	return ret;
}

struct Vector vecNormalise(struct Vector *a){
	struct Vector ret;
	float sum = a->x * a->x + a->y * a->y + a->z * a->z;
	float invsq = 1/sqrt(sum);
	ret.x = a->x * invsq;
	ret.y = a->y * invsq;
	ret.z = a->z * invsq;
	return ret;
}

float vecAngleBetween(struct Vector *a, struct Vector *b){
	float ret;
	float inside = (vecDotProduct(a, b) * (1/sqrt(a->x * a->x + a->y * a->y + a->z * a->z)) * (1/sqrt(b->x * b->x + b->y * b->y + b->z * b->z)));
	ret = acos(inside);
	return ret;

}

struct Vector linePlaneCollision(float a, float b, float c, float d, struct Vector *origin, struct Vector *direction){
	float t = (d/((a*(origin->x)+b*(origin->y)+c*(origin->z))*(a*(direction->x)+b*(direction->y)+c*(direction->z))));
	struct Vector scp = vecScalarProduct(direction, t);
	struct Vector ret = vecAdd(origin, &scp);
	return ret;

}

//4x4 matrix operations/transformations (with 4D vectors)
//matrices will be described using arrays cause it makes my life easier... 
//couldnt be bothered to do the same for the 3D vectors now that i've already written them out

float accessMatrixElement(int i, int j, float *matr_pnt){
	return *(matr_pnt + 4*j + i);
}

struct Vector4D MatrMul(float *matr_pnt, struct Vector4D *vect){
	int i, j;
	float vctr [4] = {vect->x, vect->y, vect->z, vect->w};
	float *vctr_pnt = vctr;
	for(j=0;j<4;j++){
		float row_result = 0;
		for(i=0;i<4;i++){
			float matr_num = *(matr_pnt + 4*j + i);
			float vct_num = *(vctr_pnt + i);
			row_result += matr_num*vct_num;
			vctr[i] = row_result;
		}
	}
	struct Vector4D ret = {*(vctr_pnt), *(vctr_pnt+1), *(vctr_pnt+2), *(vctr_pnt+3)};

	return ret;
}	

//array to store vertices in scene, eventually will be replaced with an array of arrays of vector structs for objects
struct Vector vertices[8];

float h = (160/(tan(FOV/2))); //distance from position to projection plane, screen dimensions are 320x240
struct Vector camPos = {0,0,0};


int main(void){
	//coordinates for a cube
	vertices[0].x = 10;
	vertices[0].y = 10;
	vertices[0].z = 0;

	vertices[1].x = 10;
	vertices[1].y = 30;
	vertices[1].z = 0;

	vertices[2].x = 30;
	vertices[2].y = 10;
	vertices[2].z = 0;

	vertices[3].x = 30;
	vertices[3].y = 10;
	vertices[3].z = 0;

	vertices[4].x = 10;
	vertices[4].y = 10;
	vertices[4].z = 20;

	vertices[5].x = 10;
	vertices[5].y = 30;
	vertices[5].z = 20;

	vertices[6].x = 30;
	vertices[6].y = 10;
	vertices[6].z = 20;

	vertices[7].x = 30;
	vertices[7].y = 10;
	vertices[7].z = 20;
	
	gfx_Begin();
	gfx_ZeroScreen();
	gfx_SetDrawBuffer();

	float h = (160/(tan(FOV/2)));

	while (!os_GetCSC()){

	}
	gfx_End();
	return 0;
}
