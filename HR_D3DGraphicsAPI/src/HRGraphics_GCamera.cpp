#include "HRGraphics_GCamera.h"

namespace HR_SDK
{
	void C_GCamera::SetPosition
	(
		const C_Vector3D prm_Position
	)
	{
		memcpy(&m_Position, &prm_Position, sizeof(C_Vector3D));
	}

	void C_GCamera::SetTarget
	(
		const C_Vector3D prm_Target
	)
	{
		memcpy(&m_Target, &prm_Target, sizeof(C_Vector3D));
	}

	void C_GCamera::SetUp
	(
		const C_Vector3D prm_Up
	)
	{
		memcpy(&m_Up, &prm_Up, sizeof(C_Vector3D));
	}

	void C_GCamera::LookAt
	(

	)
	{
		C_Vector3D XAxis, YAxis, ZAxis;

		ZAxis = m_Target - m_Position;		ZAxis.Normalize();
		XAxis = m_Up.Cross(ZAxis);			XAxis.Normalize();
		YAxis = ZAxis.Cross(XAxis);

		float X, Y, Z;

		X = XAxis.Dot(m_Position);
		Y = YAxis.Dot(m_Position);
		Z = ZAxis.Dot(m_Position);

		m_View  = C_Matrix4
		(
			XAxis.m_x,		YAxis.m_x,		ZAxis.m_x,		0.0f,
			XAxis.m_y,		YAxis.m_y,		ZAxis.m_y,		0.0f,
			XAxis.m_z,		YAxis.m_z,		ZAxis.m_z,		0.0f,
			-X,				-Y,				-Z,				1.0f
		);
	}

	void C_GCamera::Projection
	(
		float prm_FOVAngle,
		float prm_AspectRatio,
		float prm_NearZ,
		float prm_FarZ
	)
	{
		float H, W;

		H = 1.0f / C_PlatformMath::Tangent(prm_FOVAngle * (1.0f/2.0f));
		W = H * prm_AspectRatio;

		float _3rd, _4th;

		_3rd = prm_FarZ / (prm_FarZ - prm_NearZ);
		_4th = -prm_NearZ * prm_FarZ / (prm_FarZ - prm_NearZ);

		m_Projection = C_Matrix4
		(
			W,			0.0f,			0.0f,			0.0f,
			0.0f,		H,				0.0f,			0.0f,
			0.0f,		0.0f,			_3rd,			1.0f,
			0.0f,		0.0f,			_4th,			0.0f
		);
	}
}