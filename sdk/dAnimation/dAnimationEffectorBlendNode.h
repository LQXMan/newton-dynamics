/* Copyright (c) <2003-2016> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/

#ifndef __D_ANIMATION_EFFECTOR_BLEND_NODE_h__
#define __D_ANIMATION_EFFECTOR_BLEND_NODE_h__

class dAnimationEffectorBlendNode;
class dAnimIDRigEffector;
class dAnimIDController;

class dAnimationTransform
{
	public:
	dVector m_posit;
	dQuaternion m_rotation;
	dAnimIDRigEffector* m_effector;
};

class dAnimationPose: public dList<dAnimationTransform>
{
	public:
	dAnimationPose(dAnimIDController* const character);

	void SetTargetPose(dAnimIDController* const character) const;
	void CopySource(const dAnimationPose& source);
};

class dAnimationEffectorBlendNode: public dCustomAlloc
{
	public:
	dAnimationEffectorBlendNode(dAnimIDController* const character, dAnimationEffectorBlendNode* const child);
	virtual ~dAnimationEffectorBlendNode();

	virtual void Debug(dCustomJoint::dDebugDisplay* const debugContext) const
	{
		if (m_child) {
			m_child->Debug(debugContext);
		}
	}

	virtual void Evaluate(dAnimationPose& output, dFloat timestep)
	{
		if (m_child) {
			m_child->Evaluate(output, timestep);
		}
	}

	dAnimIDController* m_character;
	dAnimationEffectorBlendNode* m_child;
};

#endif