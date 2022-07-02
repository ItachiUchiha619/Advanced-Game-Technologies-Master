#include "SpringConstraint.h"

namespace NCL {
	namespace CSC8503 {
		void SpringConstraint::UpdateConstraint(float dt) {
			Vector3 relativePos = objectB->GetTransform().GetPosition() - objectA->GetTransform().GetPosition();
			Vector3 offsetPos  = relativePos - OriginalOffset;
			
			if (abs(offsetPos.z) > 0.001f) {
				PhysicsObject* physA = objectA->GetPhysicsObject();
				PhysicsObject* physB = objectB->GetPhysicsObject();

				float constraintMass = physA->GetInverseMass() + physB->GetInverseMass();

				if (constraintMass > 0.0f) {
					float biasFactor = 0.1f;
					Vector3 aImpulse = offsetPos * biasFactor;
					Vector3 bImpulse = -offsetPos * biasFactor;

					physA->AddForce(aImpulse * dt);
					physB->AddForce(bImpulse * dt);
				}
			}
		}
	}
}