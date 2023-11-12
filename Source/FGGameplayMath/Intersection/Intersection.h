#pragma once

#include "CoreMinimal.h"

UENUM()
enum EIntersection
{
	Plane,
	Sphere,
	AABB,
	Triangle,
	Ray
};