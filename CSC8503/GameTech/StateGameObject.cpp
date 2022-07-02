#include "StateGameObject.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/State.h"

using namespace NCL;
using namespace CSC8503;

StateGameObject::StateGameObject() {
	counter = 0.0f;
	stateMachine = new StateMachine();

	State* stateA = new State([&](float dt)-> void {
			this->MoveDown(dt);
		}
	);
	State* stateB = new State([&](float dt)-> void {
			this->MoveUp(dt);
		}
	);

	stateMachine->AddState(stateA);
	stateMachine->AddState(stateB);

	stateMachine->AddTransition(new StateTransition(stateA, stateB, [&]()-> bool {
			return this->counter > 0.5f;
		}
	));

	stateMachine->AddTransition(new StateTransition(stateB, stateA, [&]()-> bool {
			return this->counter < -0.5f;
		}
	));
}

StateGameObject::~StateGameObject() {
	delete stateMachine;
}

void StateGameObject::Update(float dt) {
	stateMachine->Update(dt);
}

void StateGameObject::MoveDown(float dt) {
	GetPhysicsObject()->AddForce({ 0,-80,0 });
	counter += dt;
}

void StateGameObject::MoveUp(float dt) {
	GetPhysicsObject()->AddForce({ 0,100,0 });
	counter -= dt;
}