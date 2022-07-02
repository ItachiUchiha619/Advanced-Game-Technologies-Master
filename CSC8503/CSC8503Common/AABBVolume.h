#pragma once
#include "CollisionVolume.h"
#include "../../Common/Vector3.h"
#include <algorithm>
namespace NCL {
	class AABBVolume : CollisionVolume
	{
	public:
		AABBVolume(const Vector3& halfDims) {
			type		= VolumeType::AABB;
			halfSizes	= halfDims;
		}
		~AABBVolume() {

		}

		Vector3 GetHalfDimensions() const {
			return halfSizes;
		}


		virtual Vector3 halfSize() const override {
			return halfSizes;
		}

	protected:
		Vector3 halfSizes;
	};
}
