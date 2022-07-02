#pragma once
#include "CollisionVolume.h"

#include <algorithm>
namespace NCL {
	class SphereVolume : public CollisionVolume
	{
	public:
		SphereVolume(float sphereRadius = 1.0f, float _innerRadius = 0.0f) {
			type	= VolumeType::Sphere;
			radius	= sphereRadius;
			innerRadius = _innerRadius;
		}
		~SphereVolume() {}

		float GetRadius() const {
			return radius;
		}

		
		float GetInnerRadius() const {
			return innerRadius;
		}
		

		virtual Vector3 halfSize() const override {
			return { radius,radius,radius };
		}

	protected:
		float	radius;
		float	innerRadius;
	};
}