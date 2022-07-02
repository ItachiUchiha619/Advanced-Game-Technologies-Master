#pragma once
#include "CollisionVolume.h"
#include <algorithm>
namespace NCL {
    class CapsuleVolume : public CollisionVolume
    {
    public:
        CapsuleVolume(float halfHeight, float radius) {
            this->halfHeight    = halfHeight;
            this->radius        = radius;
            this->type          = VolumeType::Capsule;
        };
        ~CapsuleVolume() {

        }
        float GetRadius() const {
            return radius;
        }

        float GetHalfHeight() const {
            return halfHeight;
        }

		virtual Vector3 halfSize() const override {
			return { radius * 2, halfHeight, radius * 2 };
		}

    protected:
        float radius;
        float halfHeight;
    };
}

