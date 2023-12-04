#include "Camera.h"
#include "VectorMath.hpp"
#include "MatrixMath.hpp"

Camera::Camera(const int w, const int h, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: attachedWindow(nullptr), width(w), height(h), fov(fov), worldPosition(pos), direction(dir), outputColor(new unsigned int[w * h]), pixelExtras(new frameExtra[w * h]),
		meshes(new Geometry* [GEOMETRIES_PER_FRAME]), meshGroups(new GeometryGroup* [GEOMETRY_GROUPS_PER_FRAME]), objectToScreenMat(), inversePointtAtMat(),
	projection(p), meshesBound(0), meshGroupsBound(0)
{
}

Camera::Camera(Window& window, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: attachedWindow(&window), width(window.getWidth()), height(window.getHeight()), fov(fov), worldPosition(pos), direction(dir), outputColor(reinterpret_cast<SDL_Surface*>(window.windowFrame)->pixels), pixelExtras(window.windowFrameExtras),
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

void Camera::setFov(const float& fov)
{
	this->fov = fov;
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
static void scanline(GrEn::Triangle& primitive, void*& outputColor, struct frameExtra* pixelExtras, int& w, int& h) {
	/*
	* A scanline based on the well known line algorithm which allows lerping with almost 0 float point arithmatic
	* the lerps are a union of a buffer holding all the lerp values and a struct that tries to easily divide the buffer to its content
	*/
	
	int x0 = static_cast<int>(primitive.vertex[0].x);
	int x1 = static_cast<int>(primitive.vertex[1].x);
	int x2 = static_cast<int>(primitive.vertex[2].x);
	int y0 = static_cast<int>(primitive.vertex[0].y);
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
	float ySlope01 = 1/(primitive.vertex[1].y-primitive.vertex[0].y);
	float ySlope02 = 1/(primitive.vertex[2].y - primitive.vertex[0].y);
	float ySlope12 = 1/(primitive.vertex[2].y - primitive.vertex[1].y);

	float lineSlope = 0;

	frag z01FragSlopes = { {(primitive.vertex[1].z - primitive.vertex[0].z) * ySlope01} };
	frag z02FragSlopes = { {(primitive.vertex[2].z - primitive.vertex[0].z) * ySlope02} };
	frag z12FragSlopes = { {(primitive.vertex[2].z - primitive.vertex[1].z) * ySlope02} };

	frag lineFrags = { {0} };

	unsigned int base = 0xff00f000;
	unsigned int col = 0;
	int fakeX0 = x0;
	int dx1 = 0, sx1 = 0;
	int dx2 = 0, sx2 = 0;
	int dy = 0, sy = 0;
	int dy2 = 0, sy2 = 0;
	int err = 0, tempErr = 0;
	int err2 = 0, tempErr2 = 0;
	int minDx = 0;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			dx1 = abs(x1 - x0); sx1 = x0 < x1 ? 1 : -1;
			dx2 = abs(x2 - x0); sx2 = x0 < x2 ? 1 : -1;
			dy = abs(y1 - y0); sy = y0 < y1 ? 1 : -1;
			dy2 = abs(y2 - y0); sy2 = y0 < y2 ? 1 : -1;
			err = (dx1 > dy ? dx1 : -dy) / 2;
			err2 = (dx2 > dy2 ? dx2 : -dy2) / 2;


			for (; x0 != x1;) {
				col++;
				tempErr = err;
				tempErr2 = err2;
				if (tempErr > -dx1 && tempErr >= dy) { err -= dy; x0 += sx1; }
				if (tempErr2 > -dx2 && tempErr2 >= dy2) { err2 -= dy2; fakeX0 += sx2; }
				if (tempErr < dy && tempErr2 < dy2) {
					err += dx1;
					err2 += dx2;
					
					lineSlope = (x0 < fakeX0 ? (x0x2Lerp.values.zBuf - x0x1Lerp.values.zBuf) / (fakeX0 - x0) : (x0x1Lerp.values.zBuf - x0x2Lerp.values.zBuf) / (x0 - fakeX0));
					lineFrags.values.zBuf = x0 < fakeX0 ? x0x1Lerp.values.zBuf  : x0x2Lerp.values.zBuf;
					for (int j = (x0 < fakeX0 ? x0 : fakeX0); j < (x0 < fakeX0 ? fakeX0 : x0); j++)
					{
						lineFrags.values.zBuf += lineSlope;
						if (0 <= j && j <= w && 0 <= y0 && y0 <= h && (pixelExtras[j + y0 * w].z > lineFrags.values.zBuf))
						{
							pixelExtras[j + y0 * w].z = lineFrags.values.zBuf;
							reinterpret_cast<unsigned int*>(outputColor)[j + y0 * w] = ((col >> 1) & 0x0000ff) + base;
						}
					}
					y0 += sy;
					x0x1Lerp.values.zBuf += z01FragSlopes.values.zBuf;
					x0x2Lerp.values.zBuf += z02FragSlopes.values.zBuf;
				}
			}


			dx1 = abs(x2 - x0); sx1 = x0 < x2 ? 1 : -1;
			dy = abs(y2 - y0); sy = y0 < y2 ? 1 : -1;
			err = (dx1 > dy ? dx1 : -dy) / 2;

			for (; x0 != x2;) {
				col++;
				tempErr = err;
				tempErr2 = err2;
				if (tempErr > -dx1 && tempErr >= dy) { err -= dy; x0 += sx1; }
				if (tempErr2 > -dx2 && tempErr2 >= dy2) { err2 -= dy2; fakeX0 += sx2; }
				if (tempErr < dy && tempErr2 < dy2) {
					err += dx1;
					err2 += dx2;

					lineSlope = (x0 < fakeX0 ? (x0x2Lerp.values.zBuf - x0x1Lerp.values.zBuf) / (fakeX0 - x0) : (x0x1Lerp.values.zBuf - x0x2Lerp.values.zBuf) / (x0 - fakeX0));
					lineFrags.values.zBuf = x0 < fakeX0 ? x0x1Lerp.values.zBuf : x0x2Lerp.values.zBuf;
					for (int j = (x0 < fakeX0 ? x0 : fakeX0); j < (x0 < fakeX0 ? fakeX0 : x0); j++)
					{
						lineFrags.values.zBuf += lineSlope;
						if (0 <= j && j <= w && 0 <= y0 && y0 <= h && (pixelExtras[j + y0 * w].z > lineFrags.values.zBuf))
						{
							pixelExtras[j + y0 * w].z = lineFrags.values.zBuf;
							reinterpret_cast<unsigned int*>(outputColor)[j + y0 * w] = ((col >> 1) & 0x0000ff) + base;
						}
					}
					y0 += sy;
					x0x1Lerp.values.zBuf += z12FragSlopes.values.zBuf;
					x0x2Lerp.values.zBuf += z02FragSlopes.values.zBuf;
				}
			}
			x0 = static_cast<int>(primitive.vertex[0].x);
			x1 = static_cast<int>(primitive.vertex[1].x);
			y0 = static_cast<int>(primitive.vertex[0].y);
			y1 = static_cast<int>(primitive.vertex[1].y);
			continue;
		case 1:
			x0 = static_cast<int>(primitive.vertex[0].x);
			x1 = static_cast<int>(primitive.vertex[2].x);
			y0 = static_cast<int>(primitive.vertex[0].y);
			y1 = static_cast<int>(primitive.vertex[2].y);
			continue;
		case 2:
			x0 = static_cast<int>(primitive.vertex[1].x);
			x1 = static_cast<int>(primitive.vertex[2].x);
			y0 = static_cast<int>(primitive.vertex[1].y);
			y1 = static_cast<int>(primitive.vertex[2].y);
			continue;
		default:
			return;
		}

		dx1 = abs(x1 - x0), sx1 = x0 < x1 ? 1 : -1;
		dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		err = (dx1 > dy ? dx1 : -dy) / 2, tempErr;

		for (;;) {

			if (0 <= primitive.vertex[0].x && primitive.vertex[0].x <= w && 0 <= primitive.vertex[0].y && primitive.vertex[0].y <= h)
			{
				reinterpret_cast<unsigned int*>(outputColor)[x0 + y0 * w] = 0xffff0000;
				col += 2;
			}
			if (x0 == x1 && y0 == y1) break;
			tempErr = err;
			if (tempErr > -dx1) { err -= dy; x0 += sx1; }
			if (tempErr < dy) { err += dx1; y0 += sy; }
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
	GrEn::mat4<float>* objectToWorldMat = nullptr;
	this->updateFields();

	for (size_t i = 0; i < this->meshGroupsBound; i++)
	{
		while (this->meshGroups[i]->iterate(renderedGeom) != GEOMETRY_END)
		{
			renderedGeom->getPos(objectToWorldMat);
			while (renderedGeom->iterate(processedPrim) != GEOMETRY_END)
			{
				//add prim transformation to camera space 
				matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[0]);
				matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[1]);
				matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[2]);
					
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
		this->meshes[i]->getPos(objectToWorldMat);
		while (this->meshes[i]->iterate(processedPrim) != GEOMETRY_END)
		{
			//add prim transformation to world space 
			matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[0]);
			matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[1]);
			matHomVecMultEq(*objectToWorldMat, processedPrim.vertex[2]);

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
	//TODO: Optimize when we start rendering/using this
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
	const float fovFactor = 1.0f/tanf(this->fov / 2);
	const float farNearFactor = FAR_PLANE / (FAR_PLANE - NEAR_PLANE);
	switch (this->projection)
	{
	case Projection::Orthographic:
		//TODO: (priority: 2) finish this
	case Projection::Perspective:
		this->objectToScreenMat[0][0] = (static_cast<float>(this->height) / this->width) * fovFactor; this->objectToScreenMat[0][1] = 0;
																				this->objectToScreenMat[0][2] = 0; this->objectToScreenMat[0][3] = 0;
		this->objectToScreenMat[1][0] = 0; this->objectToScreenMat[1][1] = fovFactor; this->objectToScreenMat[1][2] = 0;
																				this->objectToScreenMat[1][3] = 0;
		this->objectToScreenMat[2][0] = 0; this->objectToScreenMat[2][1] = 0; this->objectToScreenMat[2][2] = farNearFactor;
																				this->objectToScreenMat[2][3] = -NEAR_PLANE * farNearFactor;
		this->objectToScreenMat[3][0] = 0; this->objectToScreenMat[3][1] = 0; this->objectToScreenMat[3][2] = 1;
																				this->objectToScreenMat[3][3] = 0;
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
