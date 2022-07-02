#pragma once
#include "../CSC8503Common/GameObject.h"
namespace NCL {
	namespace CSC8503 {
		class StateMachine;
		class StateGameObject : public GameObject {
		public:
			StateGameObject();
			~StateGameObject();

			virtual void Update(float dt);

		protected:
			void MoveDown(float dt);
			void MoveUp(float dt);

			StateMachine* stateMachine;
			float counter;
		};
	}
}