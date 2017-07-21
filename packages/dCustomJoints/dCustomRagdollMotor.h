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


// dCustomBallAndSocket.h: interface for the dCustomBallAndSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _D_CUSTOM_RAG_DOLL_MOTOR_H_
#define _D_CUSTOM_RAG_DOLL_MOTOR_H_

#include "dCustomJoint.h"
#include "dCustomBallAndSocket.h"


// this joint is for controlling rag dolls muscles
class dCustomRagdollMotor: public dCustomBallAndSocket
{
	public:
	class dSaveLoad
	{
		public:
		dSaveLoad() {}
		virtual ~dSaveLoad() {}
		virtual const char* GetBodyUniqueName(const NewtonBody* const body) const = 0;

		virtual NewtonBody* Load(const char* const name);
		virtual void Save(const char* const name, NewtonBody* const roobody);
	};

	class dAngleLimit
	{
		public:
		dAngleLimit ()
			:m_angle(0.0f)
			,m_minAngle(-30.0f * 3.141592f / 180.0f)
			,m_maxAngle(30.0f * 3.141592f / 180.0f)
		{
		}

		dAngleLimit (dFloat minAngle, dFloat maxAngle)
			:m_angle(0.0f)
			,m_minAngle(minAngle)
			,m_maxAngle(maxAngle)
		{}
		dFloat m_angle;
		dFloat m_minAngle;
		dFloat m_maxAngle;
	};

	CUSTOM_JOINTS_API dCustomRagdollMotor(const dMatrix& pinAndPivotFrame, NewtonBody* const child, NewtonBody* const parent);
	CUSTOM_JOINTS_API virtual ~dCustomRagdollMotor();

	CUSTOM_JOINTS_API dFloat GetJointTorque() const;
	CUSTOM_JOINTS_API void SetJointTorque(dFloat torque);
	
	protected:
	CUSTOM_JOINTS_API dCustomRagdollMotor(NewtonBody* const child, NewtonBody* const parent, NewtonDeserializeCallback callback, void* const userData);
	CUSTOM_JOINTS_API virtual void Serialize(NewtonSerializeCallback callback, void* const userData) const;
	CUSTOM_JOINTS_API virtual void SubmitConstraints(dFloat timestep, int threadIndex);

	void CalcutaleEulers (const dMatrix& matrix0, const dMatrix& matrix1, dFloat& twist, dFloat& roll, dFloat& yaw) const;

	dFloat m_torque;
	int m_motorMode;

	DECLARE_CUSTOM_JOINT(dCustomRagdollMotor, dCustomBallAndSocket)
};


class dCustomRagdollMotor_1dof: public dCustomRagdollMotor
{
	public:
	CUSTOM_JOINTS_API dCustomRagdollMotor_1dof(const dMatrix& pinAndPivotFrame, NewtonBody* const child, NewtonBody* const parent);

	CUSTOM_JOINTS_API void SetTwistAngle(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetTwistAngle(dFloat& minAngle, dFloat& maxAngle) const;

	protected:
	CUSTOM_JOINTS_API dCustomRagdollMotor_1dof(NewtonBody* const child, NewtonBody* const parent, NewtonDeserializeCallback callback, void* const userData);
	CUSTOM_JOINTS_API virtual void Serialize(NewtonSerializeCallback callback, void* const userData) const;

	private:
	virtual void SubmitConstraints(dFloat timestep, int threadIndex);

	dAngleLimit m_twistAngle;
	DECLARE_CUSTOM_JOINT(dCustomRagdollMotor_1dof, dCustomRagdollMotor)
};

class dCustomRagdollMotor_2dof: public dCustomRagdollMotor
{
	public:
	CUSTOM_JOINTS_API dCustomRagdollMotor_2dof(const dMatrix& pinAndPivotFrame, NewtonBody* const child, NewtonBody* const parent);

	CUSTOM_JOINTS_API void SetYawAngles(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetYawAngles(dFloat& minAngle, dFloat& maxAngle) const;

	CUSTOM_JOINTS_API void SetRollAngles(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetRollAngles(dFloat& minAngle, dFloat& maxAngle) const;

	protected:
	CUSTOM_JOINTS_API dCustomRagdollMotor_2dof(NewtonBody* const child, NewtonBody* const parent, NewtonDeserializeCallback callback, void* const userData);
	CUSTOM_JOINTS_API virtual void Serialize(NewtonSerializeCallback callback, void* const userData) const;

	private:
	virtual void SubmitConstraints(dFloat timestep, int threadIndex);

	dAngleLimit m_yawAngle;
	dAngleLimit m_rollAngle;
	DECLARE_CUSTOM_JOINT(dCustomRagdollMotor_2dof, dCustomRagdollMotor)
};

class dCustomRagdollMotor_3dof: public dCustomRagdollMotor
{
	public:
	CUSTOM_JOINTS_API dCustomRagdollMotor_3dof(const dMatrix& pinAndPivotFrame, NewtonBody* const child, NewtonBody* const parent);

	CUSTOM_JOINTS_API void SetTwistAngle(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetTwistAngle(dFloat& minAngle, dFloat& maxAngle) const;

	CUSTOM_JOINTS_API void SetYawAngles(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetYawAngles(dFloat& minAngle, dFloat& maxAngle) const;

	CUSTOM_JOINTS_API void SetRollAngles(dFloat minAngle, dFloat maxAngle);
	CUSTOM_JOINTS_API void GetRollAngles(dFloat& minAngle, dFloat& maxAngle) const;

	protected:
	CUSTOM_JOINTS_API dCustomRagdollMotor_3dof(NewtonBody* const child, NewtonBody* const parent, NewtonDeserializeCallback callback, void* const userData);
	CUSTOM_JOINTS_API virtual void Serialize(NewtonSerializeCallback callback, void* const userData) const;

	private:
	virtual void SubmitConstraints(dFloat timestep, int threadIndex);

	dAngleLimit m_twistAngle;
	dAngleLimit m_yawAngle;
	dAngleLimit m_rollAngle;
	DECLARE_CUSTOM_JOINT(dCustomRagdollMotor_3dof, dCustomRagdollMotor)
};


#endif 
