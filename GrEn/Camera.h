#pragma once
#include "Window.h"
#include "GrEnDefinitions.h"
#include "GeometryGroup.h"
#include "Geometry.h"
#include "GrEnException.h"

#define GEOMETRY_GROUPS_PER_FRAME 128
#define GEOMETRIES_PER_FRAME 512

enum class Projection
{
	Perspective,
	Orthographic,
};

class Window;
class Camera
{
public:
	Camera(const int w, const int h, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p);
	Camera(Window& window, const float fov, const GrEn::vec3<float>& pos, const GrEn::vec3<float>& dir, const Projection p);

	GrEn::vec3<float> getPos() const;
	GrEn::vec3<float> getDir() const;
	float getFov() const;
	int getWidth() const;
	int getHeight() const;

	void setPos(const GrEn::vec3<float>& position);
	void setDir(const GrEn::vec3<float>& direction);
	void setFov(const float& fov);
	void setWidth(const int& width);
	void setHeight(const int& height);
	
	void getPointAtMat(GrEn::mat4<float>& mat);
	void getObjectToScreenMat(GrEn::mat4<float>& mat);

private:
	void calcPointAtMat();
	void calcObjectToScreenMat();
	void* outputColor;
	struct frameExtra* pixelExtras;
	
	GrEn::vec3<float> worldPosition;
	GrEn::vec3<float> direction;
	float fov;
	int width;
	int height;
	Projection projection;

	GrEn::mat4<float> pointAtMat;
	GrEn::mat4<float> objectToScreenMat;
	
	const GeometryGroup** meshGroups;
	const Geometry** meshes;

};

