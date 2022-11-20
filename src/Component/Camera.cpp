#include <Component/Camera.h>
#include <DirectXMath.h>
#include <basetsd.h>
#include <winnt.h>
using namespace DirectX;

Camera::Camera() {
	SetLens(0.25f * MathHelper::Pi, 1.0f, 1000.0f);
}
Camera::~Camera() {
}
void Camera::SetLens(float fovY, float zn, float zf) {
	// cache properties
	mFovY = fovY;
	mNearZ = zn;
	mFarZ = zf;
	mNearWindowHeight = 2.0f * mNearZ * tan(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tan(0.5f * mFovY);
}
void Camera::SetAspect(float aspect) {
	mAspect = aspect;
}
void Camera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&Position, pos);
	XMStoreFloat3(&Forward, L);
	XMStoreFloat3(&Right, R);
	XMStoreFloat3(&Up, U);

}

void Camera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	LookAt(P, T, U);

	
}

void Camera::UpdateProjectionMatrix() {
	if (isOrtho) {
		mFarZ = MathHelper::Max(mFarZ, mNearZ + 0.1f);
		XMMATRIX P = XMMatrixOrthographicLH(orthoSize, orthoSize, mNearZ, mFarZ);
		XMStoreFloat4x4(&Proj, P);
	} else {
		mNearZ = MathHelper::Max(mNearZ, 0.01f);
		mFarZ = MathHelper::Max(mFarZ, mNearZ + 0.1f);
		XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
		XMStoreFloat4x4(&Proj, P);
	}
}
void Camera::UpdateViewMatrix() {
	XMVECTOR R = XMLoadFloat3(&Right);
	XMVECTOR U = XMLoadFloat3(&Up);
	XMVECTOR L = XMLoadFloat3(&Forward);
	XMVECTOR P = XMLoadFloat3(&Position);

	// Keep camera's axes orthogonal to each other and of unit length.
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	// U, L already ortho-normal, so no need to normalize cross product.
	R = XMVector3Cross(U, L);

	// Fill in the view matrix entries.
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&Right, R);
	XMStoreFloat3(&Up, U);
	XMStoreFloat3(&Forward, L);

	View(0, 0) = Right.x;
	View(1, 0) = Right.y;
	View(2, 0) = Right.z;
	View(3, 0) = x;

	View(0, 1) = Up.x;
	View(1, 1) = Up.y;
	View(2, 1) = Up.z;
	View(3, 1) = y;

	View(0, 2) = Forward.x;
	View(1, 2) = Forward.y;
	View(2, 2) = Forward.z;
	View(3, 2) = z;

	View(0, 3) = 0.0f;
	View(1, 3) = 0.0f;
	View(2, 3) = 0.0f;
	View(3, 3) = 1.0f;

	//View = GetInverseTransformMatrix(Right, Up, Forward, Position);//将世界空间转变为观察空间
}

void Camera::Strafe(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&Right);
	XMVECTOR p = XMLoadFloat3(&Position);
	XMStoreFloat3(&Position, XMVectorMultiplyAdd(s, r, p));
}

void Camera::Walk(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&Forward);
	XMVECTOR p = XMLoadFloat3(&Position);
	XMStoreFloat3(&Position, XMVectorMultiplyAdd(s, l, p));
}

void Camera::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&Right), angle);

	XMStoreFloat3(&Up,   XMVector3TransformNormal(XMLoadFloat3(&Up), R));
	XMStoreFloat3(&Forward, XMVector3TransformNormal(XMLoadFloat3(&Forward), R));

	//mViewDirty = true;
}

void Camera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&Right,   XMVector3TransformNormal(XMLoadFloat3(&Right), R));
	XMStoreFloat3(&Up, XMVector3TransformNormal(XMLoadFloat3(&Up), R));
	XMStoreFloat3(&Forward, XMVector3TransformNormal(XMLoadFloat3(&Forward), R));

	//mViewDirty = true;
}