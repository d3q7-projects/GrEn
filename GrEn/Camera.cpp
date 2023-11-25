#include "Camera.h"

Camera::Camera(const int w, const int h, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: width(w), height(h), fov(fov), worldPosition(pos), direction(dir), outputColor(new unsigned int[w * h]), pixelExtras(new frameExtra[w * h]),
		meshes(new const Geometry* [GEOMETRIES_PER_FRAME]), meshGroups(new const GeometryGroup* [GEOMETRY_GROUPS_PER_FRAME]), objectToScreenMat(), pointAtMat(),
	projection(p)
{
}

Camera::Camera(Window& window, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p)
	: width(window.getWidth()), height(window.getHeight()), fov(fov), worldPosition(pos), direction(dir), outputColor(reinterpret_cast<SDL_Surface*>(window.windowFrame)->pixels), pixelExtras(window.windowFrameExtras),
	meshes(new const Geometry* [GEOMETRIES_PER_FRAME]), meshGroups(new const GeometryGroup* [GEOMETRY_GROUPS_PER_FRAME]), objectToScreenMat(), pointAtMat(),
	projection(p)
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

void Camera::getPointAtMat(GrEn::mat4<float>& mat)
{
	this->calcPointAtMat();
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat[i][j] = this->pointAtMat[i][j];
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

void Camera::calcPointAtMat()
{
}

void Camera::calcObjectToScreenMat()
{
}
