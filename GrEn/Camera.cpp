#include "Camera.h"
#include <SDL.h>
#include "VectorMath.hpp"
#include "MatrixMath.hpp"

Camera::Camera(const int w, const int h, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: attachedWindow(nullptr), width(w), height(h), fov(static_cast<float>(M_PI)* fov / 180.0f), worldPosition(pos), direction(dir), outputColor(new unsigned int[w * h]), pixelExtras(new frameExtra[w * h]),
		meshes(new Geometry* [GEOMETRIES_PER_FRAME]), meshGroups(new GeometryGroup* [GEOMETRY_GROUPS_PER_FRAME]), objectToScreenMat(), inversePointtAtMat(),
	projection(p), meshesBound(0), meshGroupsBound(0)
{
}

Camera::Camera(Window& window, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: attachedWindow(&window), width(window.getWidth()), height(window.getHeight()), fov(static_cast<float>(M_PI)* fov / 180.0f), worldPosition(pos), direction(dir), outputColor(reinterpret_cast<SDL_Surface*>(window.windowFrame)->pixels), pixelExtras(window.windowFrameExtras),
	meshes(new Geometry* [GEOMETRIES_PER_FRAME]), meshGroups(new GeometryGroup* [GEOMETRY_GROUPS_PER_FRAME]), objectToScreenMat(), inversePointtAtMat(),
	projection(p), meshesBound(0), meshGroupsBound(0)
{
}

GrEn::vec3<float> Camera::getPos() const
{
	return this->worldPosition;
}

GrEn::vec3<float> Camera::getDir() const
{
	return this->direction;
}

float Camera::getFov() const
{
	return this->fov;
}

int Camera::getWidth() const
{
	return this->width;
}

int Camera::getHeight() const
{
	return this->height;
}

void Camera::setPos(const GrEn::vec3<float>& position)
{
	this->worldPosition = position;
}

void Camera::setDir(const GrEn::vec3<float>& direction)
{
	this->direction = direction;
}

void Camera::setFovDegree(const float& fov)
{
	this->fov = static_cast<float>(M_PI) * fov / 180.0f;
}

void Camera::setFovRadians(const float& fov)
{
	this->fov = fov;
}

void Camera::addFovDegree(const float& fov)
{
	this->fov += static_cast<float>(M_PI) * fov / 180.0f;
}

void Camera::addFovRadians(const float& fov)
{
	this->fov += fov;
}

void Camera::setWidth(const int& width)
{
	this->width = width;
}

void Camera::setHeight(const int& height)
{
	this->width = height;
}

void Camera::getInversePointAtMat(GrEn::mat4<float>& mat)
{
	this->calcInversePointAtMat();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat[i][j] = this->inversePointtAtMat[i][j];
		}
	}
}

void Camera::getObjectToScreenMat(GrEn::mat4<float>& mat)
{
	this->calcObjectToScreenMat();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat[i][j] = this->objectToScreenMat[i][j];
		}
	}
}

void Camera::addGeometry(Geometry* mesh)
{
	if (mesh && this->meshesBound < GEOMETRIES_PER_FRAME) {
		this->meshes[meshesBound] = mesh;
		this->meshesBound++;
	}
}

void Camera::addGeometryGroup(GeometryGroup* mesh)
{
	if (mesh && this->meshGroupsBound < GEOMETRY_GROUPS_PER_FRAME) {
		this->meshGroups[meshGroupsBound] = mesh;
		this->meshGroupsBound++;
	}
}

/// <summary>
/// This scanline function goes over the lines of triangles using the frame and triangle info
/// it lerps over the attributes of the triangle's vertices and draws it on screen after frag-calculations(shaders).
/// 
/// In the future this function will be multi-threaded on the cpu to render multiple triangles at the same time(for non-gpu usage)
/// </summary>
static inline void scanline(GrEn::Triangle& primitive, void*& outputColor, struct frameExtra* pixelExtras, int& w, int& h) {
	/*
	* A scanline based on the well known line algorithm which allows lerping with almost 0 float point arithmatic
	* the lerps are a union of a buffer holding all the lerp values and a struct that tries to easily divide the buffer to its content
	*/
	
	int x01 = static_cast<int>(primitive.vertex[0].x);
	int x02 = static_cast<int>(primitive.vertex[0].x);
	int x1 = static_cast<int>(primitive.vertex[1].x);
	int x2 = static_cast<int>(primitive.vertex[2].x);
	int y01 = static_cast<int>(primitive.vertex[0].y);
	int y02 = static_cast<int>(primitive.vertex[0].y);
	int y1 = static_cast<int>(primitive.vertex[1].y);
	int y2 = static_cast<int>(primitive.vertex[2].y);

	/*
	* Here we define the "side-lerpers" that lerp through the values of the triangle.
	* Unlike the triangle's position, we must lerp the attributes unefficiently with floats, as we need the exact values in the pixels.
	* Right now we manually assign the values. Later, we will initialize it using the loop array on the frag union.
	*/
	frag x0x1Lerp = { {primitive.vertex[0].z} };
	frag x0x2Lerp = { {primitive.vertex[0].z} };

	//if any of the divisions is by 0 then it will be skipped as the primitives wont be drawn
	float ySlope01 = 1/(primitive.vertex[1].y - primitive.vertex[0].y);
	float ySlope02 = 1/(primitive.vertex[2].y - primitive.vertex[0].y);
	float ySlope12 = 1/(primitive.vertex[2].y - primitive.vertex[1].y);

	float lineSlope = 0;

	frag z01FragSlopes = { {(primitive.vertex[1].z - primitive.vertex[0].z) * ySlope01} };
	frag z02FragSlopes = { {(primitive.vertex[2].z - primitive.vertex[0].z) * ySlope02} };
	frag z12FragSlopes = { {(primitive.vertex[2].z - primitive.vertex[1].z) * ySlope12} };

	frag lineFrags = { {0} };
	frag lineSlopes = { {0} };

	int dx01 = abs(x1 - x01), sx01 = x01 < x1 ? 1 : -1;
	int dy01 = abs(y1 - y01), sy01 = y01 < y1 ? 1 : -1;
	int err01 = (dx01 > dy01 ? dx01 : -dy01) / 2, tempErr01 = 0;

	int dx02 = abs(x2 - x02), sx02 = x02 < x2 ? 1 : -1;
	int dy02 = abs(y2 - y02), sy02 = y02 < y2 ? 1 : -1;
	int err02 = (dx02 > dy02 ? dx02 : -dy02) / 2, tempErr02 = 0;

	int draw01 = 0, draw02= 0;
	bool do01 = true, do02= true;

	unsigned int base2 = 0xfff00000;
	unsigned int col = 0;

	for (;;) {
		
		if (do01)
		{
			draw01 = x01;
			if (x01 == x1 && y01 == y1) {
				dx01 = abs(x2 - x01), sx01 = x01 < x2 ? 1 : -1;
				dy01 = abs(y2 - y01), sy01 = y01 < y2 ? 1 : -1;
				err01 = (dx01 > dy01 ? dx01 : -dy01) / 2, tempErr01;
				z01FragSlopes.values.zBuf = z12FragSlopes.values.zBuf;
			}
			if (x01 == x2 && y01 == y2) break;
			tempErr01 = err01;
			if (tempErr01 > -dx01) { err01 -= dy01; x01 += sx01; }
			if (tempErr01 < dy01) { err01 += dx01; y01 += sy01;
				do01 = false;
			}
		}

		if (do02)
		{
			draw02 = x02;
			tempErr02 = err02;
			if (tempErr02 > -dx02) { err02 -= dy02; x02 += sx02; }
			if (tempErr02 < dy02) { err02 += dx02; y02 += sy02;
				do02 = false;
			}
		}

		if (!(do01 || do02)) {
			lineSlope = draw01 < draw02 ? (x0x2Lerp.values.zBuf - x0x1Lerp.values.zBuf) / (draw02 - draw01) : (x0x1Lerp.values.zBuf - x0x2Lerp.values.zBuf) / (draw01 - draw02);
			lineFrags.values.zBuf = draw01 < draw02 ? x0x1Lerp.values.zBuf : x0x2Lerp.values.zBuf;
			y01--;
			y02--;
			for (int scanlineX = (draw01 < draw02 ? draw01 : draw02); scanlineX <= (draw01 < draw02 ? draw02 : draw01); scanlineX++)
			{
				if (0 <= scanlineX && scanlineX < w && 0 <= y01 && y01 < h && (pixelExtras[scanlineX + y01 * w].z > lineFrags.values.zBuf))
				{
					pixelExtras[scanlineX + y01 * w].z = lineFrags.values.zBuf;
					const int zCol = lineFrags.values.zBuf * 0xff;
					reinterpret_cast<unsigned int*>(outputColor)[scanlineX + y01 * w] = base2 + ((col >> 1) & 0x0000ff);// (zCol << 16) + (zCol << 8) + (zCol) + ;
				}
				lineFrags.values.zBuf += lineSlope;
			}
			col+=2;

			y01++; y02++; do01 = true; do02 = true;
			x0x1Lerp.values.zBuf += z01FragSlopes.values.zBuf;
			x0x2Lerp.values.zBuf += z02FragSlopes.values.zBuf;
		}
	}
}

static inline void sortPrim(GrEn::Triangle& t) {
	if (t.vertex[1].y > t.vertex[0].y)
	{
		std::swap(t.vertex[1], t.vertex[0]);
		std::swap(t.uv[1], t.uv[0]);
		std::swap(t.normal[1], t.normal[0]);
	}
	if (t.vertex[2].y > t.vertex[0].y)
	{
		std::swap(t.vertex[2], t.vertex[0]);
		std::swap(t.uv[2], t.uv[0]);
		std::swap(t.normal[2], t.normal[0]);
	}
	if (t.vertex[2].y > t.vertex[1].y)
	{
		std::swap(t.vertex[2], t.vertex[1]);
		std::swap(t.uv[2], t.uv[1]);
		std::swap(t.normal[2], t.normal[1]);
	}
}

static inline void expandPrim(GrEn::Triangle& t, int hw, int hh) {
	t.vertex[0].x += 1;
	t.vertex[0].y *= -1;
	t.vertex[0].y += 1;
	t.vertex[1].x += 1;
	t.vertex[1].y *= -1;
	t.vertex[1].y += 1;
	t.vertex[2].x += 1;
	t.vertex[2].y *= -1;
	t.vertex[2].y += 1;

	t.vertex[0].x *= hw;
	t.vertex[0].y *= hh;
	t.vertex[1].x *= hw;
	t.vertex[1].y *= hh;
	t.vertex[2].x *= hw;
	t.vertex[2].y *= hh;
}

void Camera::render()
{
	GrEn::Triangle processedPrim = { 0 };
	GrEn::Triangle renderedPrim = { 0 };
	Geometry* renderedGeom = nullptr;
	this->calcInversePointAtMat();
	this->calcObjectToScreenMat();
	int halvedWidth = this->width >> 1;
	int halvedHeight = this->height >> 1;
	GrEn::mat4<float> objectToWorldMat;
	this->updateFields();

	for (size_t i = 0; i < this->meshGroupsBound; i++)
	{
		while (this->meshGroups[i]->iterate(renderedGeom) != GEOMETRY_END)
		{
			renderedGeom->getWorldMat(objectToWorldMat);
			while (renderedGeom->iterate(processedPrim) != GEOMETRY_END)
			{
				//add prim transformation to camera space 
				matHomVecMultEq(objectToWorldMat, processedPrim.vertex[0]);
				matHomVecMultEq(objectToWorldMat, processedPrim.vertex[1]);
				matHomVecMultEq(objectToWorldMat, processedPrim.vertex[2]);
					
				//add filtering functions like frustum culling, backface culling etc.
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[0], renderedPrim.vertex[0]);
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[1], renderedPrim.vertex[1]);
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[2], renderedPrim.vertex[2]);

				
				sortPrim(renderedPrim);
				expandPrim(renderedPrim, halvedWidth, halvedHeight);
				scanline(renderedPrim, this->outputColor, this->pixelExtras, this->width, this->height);
			}
			renderedGeom->resetIteration();
		}
		this->meshGroups[i]->resetIteration();
	}

	for (size_t i = 0; i < this->meshesBound; i++)
	{
		this->meshes[i]->getWorldMat(objectToWorldMat);
		while (this->meshes[i]->iterate(processedPrim) != GEOMETRY_END)
		{
			//add prim transformation to world space 
			matHomVecMultEq(objectToWorldMat, processedPrim.vertex[0]);
			matHomVecMultEq(objectToWorldMat, processedPrim.vertex[1]);
			matHomVecMultEq(objectToWorldMat, processedPrim.vertex[2]);

			//add filtering functions like frustum culling, backface culling etc.
			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[0], renderedPrim.vertex[0]);
			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[1], renderedPrim.vertex[1]);
			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[2], renderedPrim.vertex[2]);

			sortPrim(renderedPrim);
			expandPrim(renderedPrim, halvedWidth, halvedHeight);
			scanline(renderedPrim, this->outputColor, this->pixelExtras, this->width, this->height);
		}
		this->meshes[i]->resetIteration();
	}
	this->meshGroupsBound = 0;
	this->meshesBound = 0;
}

void Camera::calcInversePointAtMat()
{
	//TODO: Fix when we start rendering/using this
	GrEn::vec3<float> forward = { 0,0,0 };
	GrEn::vec3<float> a;
	GrEn::vec3<float> newUp;
	GrEn::vec3<float> newRight;

	GrEn::vec3<float> pos = this->worldPosition;
	GrEn::vec3<float> up = { 0,1,0 };
	GrEn::vec3<float> target;
	vecAdd(this->worldPosition, this->direction, target);
	
	vecNormalize(this->direction);

	vecScalarMul(this->direction, vecDotProd(up, forward), a);
	vecSub(up, a, newUp);
	vecNormalize(newUp);

	vecCrossProd(newUp, this->direction, newRight);

	this->inversePointtAtMat[0][0] = newRight.x; this->inversePointtAtMat[0][1] = newUp.x; this->inversePointtAtMat[0][2] = this->direction.x; this->inversePointtAtMat[0][3] = 0;
	this->inversePointtAtMat[1][0] = newRight.y; this->inversePointtAtMat[1][1] = newUp.y; this->inversePointtAtMat[1][2] = this->direction.y; this->inversePointtAtMat[1][3] = 0;
	this->inversePointtAtMat[2][0] = newRight.z; this->inversePointtAtMat[2][1] = newUp.z; this->inversePointtAtMat[2][2] = this->direction.z; this->inversePointtAtMat[2][3] = 0;
	this->inversePointtAtMat[3][0] = -vecDotProd(pos, newRight); this->inversePointtAtMat[3][1] = -vecDotProd(pos, newUp); this->inversePointtAtMat[3][2] = -vecDotProd(pos, forward); this->inversePointtAtMat[3][3] = 1;
}

void Camera::calcObjectToScreenMat()
{
	const float fovFactor = 1.0f / (tanf(this->fov / 2.0f));
	const float farNearFactor = -FAR_PLANE / (FAR_PLANE - NEAR_PLANE);
	switch (this->projection)
	{
	case Projection::Orthographic:
		//TODO: (priority: 2) finish this
	case Projection::Perspective:
		this->objectToScreenMat[0][0] = (static_cast<float>(this->height) / static_cast<float>(this->width)) * fovFactor;
											this->objectToScreenMat[0][1] = 0;			this->objectToScreenMat[0][2] = 0;				this->objectToScreenMat[0][3] = 0;

		this->objectToScreenMat[1][0] = 0;	this->objectToScreenMat[1][1] = fovFactor;	this->objectToScreenMat[1][2] = 0;				this->objectToScreenMat[1][3] = 0;

		this->objectToScreenMat[2][0] = 0;	this->objectToScreenMat[2][1] = 0;			this->objectToScreenMat[2][2] = farNearFactor;	this->objectToScreenMat[2][3] = NEAR_PLANE * farNearFactor;

		this->objectToScreenMat[3][0] = 0;	this->objectToScreenMat[3][1] = 0;			this->objectToScreenMat[3][2] = 1;				this->objectToScreenMat[3][3] = 0;
		break;
	default:
		break;
	}
}

void Camera::updateFields()
{
	if (this->attachedWindow)
	{
		this->height = attachedWindow->getHeight();
		this->width = attachedWindow->getWidth();
		this->outputColor = reinterpret_cast<SDL_Surface*>(attachedWindow->windowFrame)->pixels;
		this->pixelExtras = attachedWindow->windowFrameExtras;
	}
}
