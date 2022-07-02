#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include "StateGameObject.h"
#include "../CSC8503Common/NavigationGrid.h"

namespace NCL {
	namespace CSC8503 {
		class character {
		public:
			void SetPosition(Vector3 _position) { position = _position; }
			Vector3 GetPosition() { return position; }
			void SetMaxVelocity(Vector3 _maxVel) { MaxVelocity = _maxVel; }
			Vector3 GetMaxVelocity() { return MaxVelocity; }

		private:
			Vector3 position;
			Vector3 MaxVelocity;
		};

		class Bot : public character {
		public:
			Bot() {
				SetPosition(Vector3(10, 0, 10));
				SetMaxVelocity(Vector3(3, 0, 3));
			}
			~Bot();
			void FindPlayer(Vector3 botPosition, Vector3 playerPosition) {
				NavigationGrid grid("Maze.txt");
				NavigationPath outPath;

				Vector3 startPos = botPosition;
				Vector3 endPos = playerPosition;

				bool found = grid.FindPath(startPos, endPos, outPath);

				if (found) {
					ClearNodes();
				}

				Vector3 pos;
				while (outPath.PopWaypoint(pos)) {
					testNodes.push_back(pos);
				}
			}

			void ClearNodes() { testNodes.clear(); }

			vector<Vector3> GettestNodes() { return testNodes; }

			void DisplayPathfinding() {
				for (int i = 1; i < testNodes.size(); ++i) {
					Vector3 a = testNodes[i - 1];
					Vector3 b = testNodes[i];

					Debug::DrawLine(a, b, Vector4(1, 0, 0, 1));
				}
			}
		protected:
			vector<Vector3> testNodes;
		};

		class Player : public character {
		public:
			Player() {
				SetPosition(Vector3(80, 0, 80));
				SetMaxVelocity(Vector3(3, 0, 3));
			}
			~Player();
		};

		class Goals : public character {
		public:
			Goals() {
				SetPosition(Vector3(90, 0, 90));
				SetMaxVelocity(Vector3(3, 0, 3));
			}
			~Goals();
		};

		class TutorialGame		{
		public:
			TutorialGame();
			~TutorialGame();

			virtual bool UpdateGame(float dt);

			int GetSceneState() { return sceneState; }

		protected:
			void SetSceneState(int state) { sceneState = state; }

			void InitialiseAssets();

			void InitCamera();
			void InitCameraLevel1();

			void UpdateKeys();

			void InitWorld();

			void InitGameExamples();

			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius, float innerRadius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);
			void InitFirstLevel();
			void InitSecondLevel();
			void InitDefaultFloor();

			void MainMenu(); //Main Menue for Selecting Level or Quit Game
			void GoalMenu(); //For first Level, after Goal
			void ScoreMenu(); //For Second Level, after Escape
		
			bool SelectObject();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void ChangeCollisionLayer();
			void LockedObjectMovement();

			GameObject* AddFloorToWorld(const Vector3& position);
			GameObject* AddSphereToWorld(const Vector3& position, float radius, float innerRadius, int layer, float inverseMass = 10.0f, string name = "Sphere");
			GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions, Quaternion orientation, int layer, bool aabb = true, float inverseMass = 10.0f, string name = "Cube");
			
			GameObject* AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass = 10.0f);

			GameObject* AddPlayerToWorld(const Vector3& position);
			GameObject* AddEnemyToWorld(const Vector3& position);
			GameObject* AddBonusToWorld(const Vector3& position);

			StateGameObject* AddStateObjectToWorld(const Vector3& position);

			GameTechRenderer*	renderer;
			PhysicsSystem*		physics;
			GameWorld*			world;

			bool useGravity;
			bool inSelectionMode;
			int layer;

			float		forceMagnitude;

			GameObject* selectionObject = nullptr;
			GameObject* lookedObject	= nullptr;

			OGLMesh*	capsuleMesh = nullptr;
			OGLMesh*	cubeMesh	= nullptr;
			OGLMesh*	sphereMesh	= nullptr;
			OGLTexture* basicTex	= nullptr;
			OGLShader*	basicShader = nullptr;

			//Coursework Meshes
			OGLMesh*	charMeshA	= nullptr;
			OGLMesh*	charMeshB	= nullptr;
			OGLMesh*	enemyMesh	= nullptr;
			OGLMesh*	bonusMesh	= nullptr;

			//Coursework Additional functionality	
			GameObject* lockedObject	= nullptr;
			Vector3 lockedOffset		= Vector3(0, 14, 20);
			void LockCameraToObject(GameObject* o) {
				lockedObject = o;
			}

			GameObject* FirstLevel;
			GameObject* SecondLevel;
			GameObject* Quit;
			GameObject* BackMenu;

			GameObject* MainSphere;
			GameObject* Goal;

			Vector3 MainSpherePos;

			GameObject* PlayerSphere;
			GameObject* Player1;
			GameObject* EnemySphere;
			GameObject* MazeGoal;

			bool KeepForce = false;
			/*
			sceneState 0: Main Menu
			sceneState 1: First Level
			sceneState 2: Goal Menu
			sceneState 3: Second Level
			sceneState 4: Score Menu
			*/
			float time;
			std::string timeString;
			int score;
			std::string scoreString;
			int sceneState = 0;

			bool onGoing;

			Bot* bot;
			Player* player;
			
			
		};
	}
}

