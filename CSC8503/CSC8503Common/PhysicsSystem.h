#pragma once
#include "../CSC8503Common/GameWorld.h"
#include <set>

namespace NCL {
	namespace CSC8503 {
		class PhysicsSystem	{
		public:
			PhysicsSystem(GameWorld& g);
			~PhysicsSystem();

			void Clear();

			void Update(float dt);

			void UseGravity(bool state) {
				applyGravity = state;
			}

			void SetGlobalDamping(float d) {
				globalDamping = d;
			}

			void SetGravity(const Vector3& g);
			Vector3 GetGravity() { return gravity; }

			void SetButtonState(bool pressed) { buttonPressed = pressed; }
			bool GetButtonState() { return buttonPressed; }

			void SetGravityState(bool gravityState) { antiGravity = gravityState; }
			bool GetGravityState() { return antiGravity; }

			void SetgoalState(bool goal) { reachedGoal = goal; }
			bool GetgoalState() { return reachedGoal; }

			void SetCatchState(bool _catch) { getCatch = _catch; }
			bool GetCatchState() { return getCatch; }

			void SetReachMazeGoal(bool mazegoal) { reachMazeGoal = mazegoal; }
			bool GetReachMazeGoal() { return reachMazeGoal; }

			void SetReset(bool _reset) { reset = _reset; }
			bool GetReset() { return reset; }

		protected:
			void BasicCollisionDetection();
			void BroadPhase();
			void NarrowPhase();

			void ClearForces();

			void IntegrateAccel(float dt);
			void IntegrateVelocity(float dt);

			void UpdateConstraints(float dt);

			void UpdateCollisionList();
			void UpdateObjectAABBs();

			void ImpulseResolveCollision(GameObject& a , GameObject&b, CollisionDetection::ContactPoint& p) const;

			float GetLinearDamping() { return linearDamping; }
			void SetLinearDamping(float _linearDamping) { linearDamping = _linearDamping; }

			GameWorld& gameWorld;

			bool	applyGravity;
			Vector3 gravity;
			float	dTOffset;
			float	globalDamping;
			float linearDamping;

			std::set<CollisionDetection::CollisionInfo> allCollisions;
			std::set<CollisionDetection::CollisionInfo> broadphaseCollisions;
			
			bool buttonPressed = false;
			bool useBroadPhase		= true;
			int numCollisionFrames	= 5;
			bool antiGravity = false;
			bool reachedGoal = false;
			bool getCatch = false;
			bool reachMazeGoal = false;
			bool reset = false;
		};
	}
}