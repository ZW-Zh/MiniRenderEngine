#pragma once
#include <DirectXMath.h>
#include <stdafx.h>
#include <Utility/MathHelper.h>

class Camera final {
public:
	~Camera();
	Camera();
	//  frustum properties.
	float NearZ() const { return mNearZ; }
	float FarZ() const { return mFarZ; }
	float Aspect() const { return mAspect; }
	float FovY() const { return mFovY; }
	float FovX() const {
		float halfWidth = 0.5 * NearWindowWidth();
		return 2.0 * atan(halfWidth / mNearZ);
	}

	//  near and far plane dimensions in view space coordinates.
	float NearWindowWidth() const { return mAspect * mNearWindowHeight; }
	float NearWindowHeight() const { return mNearWindowHeight; }
	float FarWindowWidth() const { return mAspect * mFarWindowHeight; }
	float FarWindowHeight() const { return mFarWindowHeight; }

	// Set frustum.
	void SetLens(float fovY, float zn, float zf);
	void SetAspect(float aspect);
	// Define camera space via LookAt parameters.
	void LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp);
	void LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up);
	
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
	DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
	DirectX::XMFLOAT3 Position = {0.0f, 0.0f, 0.0f};
	DirectX::XMFLOAT3 Right = {1.0f, 0.0f, 0.0f};
	DirectX::XMFLOAT3 Up = {0.0f, 1.0f, 0.0f};
	DirectX::XMFLOAT3 Forward = {0.0f, 0.0f, 1.0f};
	float orthoSize = 5;
	bool isOrtho = false;

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);//左右平移
	void Walk(float d);//上下移动
	
	// Rotate the camera.
	void Pitch(float angle);//上下旋转
	void RotateY(float angle);//左右旋转
private:
	float mNearZ = 0.0f;
	float mFarZ = 0.0f;
	float mAspect = 1.0f;
	float mFovY = 0.0f;
	float mNearWindowHeight = 0.0f;
	float mFarWindowHeight = 0.0f;
	
};
