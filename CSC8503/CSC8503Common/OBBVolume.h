#pragma once
#include "CollisionVolume.h"
#include "../../Common/Vector3.h"

#include <algorithm>
namespace NCL {
	class OBBVolume : CollisionVolume
	{
	public:
		OBBVolume(const Maths::Vector3& halfDims) {
			type		= VolumeType::OBB;
			halfSizes	= halfDims;
		}
		~OBBVolume() {}

		Maths::Vector3 GetHalfDimensions() const {
			return halfSizes;
		}
		virtual Vector3 halfSize() const override {
			return halfSizes;
		}

	protected:
		Maths::Vector3 halfSizes;
	};
}

