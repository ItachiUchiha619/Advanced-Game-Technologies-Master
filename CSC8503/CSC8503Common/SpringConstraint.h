#pragma once
#include "../CSC8503Common/GameWorld.h"
#include "Constraint.h"

namespace NCL {
	namespace CSC8503 {
		class GameObject;

		class SpringConstraint : public Constraint {
		public:
			SpringConstraint(GameObject* a, GameObject* b, Vector3 OriOffset, Vector3 _direction) {
				objectA = a;
				objectB = b;
				OriginalOffset = OriOffset;
				direction = _direction;
			}
			~SpringConstraint() {}

			void UpdateConstraint(float dt) override;

		protected:
			GameObject* objectA;
			GameObject* objectB;

			Vector3 OriginalOffset;
			Vector3 direction;
		};
	}
}