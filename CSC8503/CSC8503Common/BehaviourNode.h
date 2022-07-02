#pragma once
#include <string>
#include <vector>
#include <functional>

enum BehaviourState {
	Initialise,
	Failure,
	Success,
	Ongoing
};

class BehaviourNode {
public:
	BehaviourNode(const std::string& nodeName) {
		currentState = Initialise;
		name = nodeName;
	}
	virtual ~BehaviourNode() {}
	virtual BehaviourState Execute(float dt) = 0;

	virtual void Reset() { currentState = Initialise; }
protected:
	BehaviourState currentState;
	std::string name;
};

class BehaviourNodeWithChildren : public BehaviourNode {
public:
	BehaviourNodeWithChildren(const std::string& nodeName) : BehaviourNode(nodeName) {};

	~BehaviourNodeWithChildren() {
		for (auto& i : childNodes) {
			delete i;
		}
	}

	void AddChild(BehaviourNode* n) {
		childNodes.emplace_back(n);
	}

	void Reset() override {
		currentState = Initialise;
		for (auto& i : childNodes) {
			i->Reset();
		}
	}
protected:
	std::vector<BehaviourNode*> childNodes;
};

class BehaviourSelector : public BehaviourNodeWithChildren {
public:
	BehaviourSelector(const std::string& nodeName) : BehaviourNodeWithChildren(nodeName) {}
	~BehaviourSelector() {}
	BehaviourState Execute(float dt) override {
		for (auto& i : childNodes) {
			BehaviourState nodeState = i->Execute(dt);
			switch (nodeState) {
				case Failure: continue;
				case Success:
				case Ongoing:
				{
					currentState = nodeState;
					return currentState;
				}
			}
		}
		return Failure;
	}
};

class BehaviourSequence : public BehaviourNodeWithChildren {
public:
	BehaviourSequence(const std::string& nodeName) : BehaviourNodeWithChildren(nodeName) {}
	~BehaviourSequence() {}
	BehaviourState Execute(float dt) override {
		for (auto& i : childNodes) {
			BehaviourState nodeState = i->Execute(dt);
			switch (nodeState) {
				case Success: continue;
				case Failure:
				case Ongoing:
				{
					currentState = nodeState;
					return nodeState;
				}
			}
		}
		return Success;
	}
};

typedef std::function < BehaviourState(float, BehaviourState)> BehaviourActionFunc;

class BehaviourAction : public BehaviourNode {
public:
	BehaviourAction(const std::string& nodeName, BehaviourActionFunc f) : BehaviourNode(nodeName) {
		function = f;
	}
	BehaviourState Execute(float dt) override {
		currentState = function(dt, currentState);
		return currentState;
	}
protected:
	BehaviourActionFunc function;
};