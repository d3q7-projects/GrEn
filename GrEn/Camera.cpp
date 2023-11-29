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

static void scanline(GrEn::Triangle& top, void*& outputColor, struct frameExtra*& pixelExtras) {
	GrEn::Triangle bottom = top;
	
	if (true)
	{

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
	t.vertex[0].y += 1;
	t.vertex[1].x += 1;
	t.vertex[1].y += 1;
	t.vertex[2].x += 1;
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

	this->updateFields();

	for (size_t i = 0; i < this->meshGroupsBound; i++)
	{
		while (this->meshGroups[i]->iterate(renderedGeom) != GEOMETRY_END)
		{
			while (renderedGeom->iterate(processedPrim) != GEOMETRY_END)
			{
				//add prim transformation to camera space 
					
				//add filtering functions like frustum culling, backface culling etc.
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[0], renderedPrim.vertex[0]);
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[1], renderedPrim.vertex[1]);
				matHomVecMult(this->objectToScreenMat, processedPrim.vertex[2], renderedPrim.vertex[2]);


				sortPrim(renderedPrim);
				expandPrim(renderedPrim, halvedWidth, halvedHeight);
				scanline(renderedPrim, this->outputColor, this->pixelExtras);
			}
			renderedGeom->resetIteration();
		}
		this->meshGroups[i]->resetIteration();
	}

	for (size_t i = 0; i < this->meshesBound; i++)
	{
		while (this->meshes[i]->iterate(processedPrim) != GEOMETRY_END)
		{
			//add prim transformation to world space 

			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[0], renderedPrim.vertex[0]);
			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[1], renderedPrim.vertex[1]);
			matHomVecMult(this->objectToScreenMat, processedPrim.vertex[2], renderedPrim.vertex[2]);

			scanline(renderedPrim, this->outputColor, this->pixelExtras);
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
		this->outputColor = attachedWindow->windowFrame;
		this->pixelExtras = attachedWindow->windowFrameExtras;
	}
}
