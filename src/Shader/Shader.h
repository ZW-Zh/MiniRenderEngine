#pragma once
#include <stdafx.h>
#include <DXSampleHelper.h>
#include <Windows.h>
#include <d3dx12.h>
#include <Shader/ShaderVariableType.h>
#include <Resource/Buffer.h>
#include <unordered_map>
#include <optional>
#include <Resource/DescriptorHeapView.h>

using Microsoft::WRL::ComPtr;
class TopAccel;
class Shader {
public:
	struct Property {
		ShaderVariableType type;
		uint spaceIndex;//寄存器空间
		uint registerIndex;//绑定的基准着色器寄存器1 SRV t1，sampler s，UAV u，CBV b
		uint arrSize;//描述符range中描述符个数
	};
protected:
	struct InsideProperty : public Property {
		uint rootSigPos;
		InsideProperty(Property const& p)
			: Property(p) {}
	};
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSig;
	std::unordered_map<std::string, InsideProperty> properties;
	std::optional<InsideProperty> GetProperty(std::string_view str) const;//c++ 17规范，用来处理对象可能为空的情况，option对象可以隐式转换为boolean类型

public:
	Shader(
		std::span<std::pair<std::string, Property> const> properties,
		Device* device);//内部创建了根签名
	Shader(
		std::span<std::pair<std::string, Property> const> properties,
		ComPtr<ID3D12RootSignature>&& rootSig);
	Shader(Shader&& v) = default;
	ID3D12RootSignature* RootSig() const { return rootSig.Get(); }

	bool SetResource(
		std::string_view propertyName,
		ID3D12GraphicsCommandList* cmdList,
		BufferView buffer) const;
	bool SetResource(
		std::string_view propertyName,
		ID3D12GraphicsCommandList* cmdList,
		DescriptorHeapView buffer) const;
	virtual ~Shader() = default;
};
