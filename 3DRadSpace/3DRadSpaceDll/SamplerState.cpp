#include "SamplerState.h"

#ifdef __DIRECTXVER

SamplerState::SamplerState(ID3D11Device* device)
{
    _samplerstate = nullptr;

    //generate default values
    D3D11_SAMPLER_DESC samplerstatedesc;
    memset(&samplerstatedesc, 0, sizeof(samplerstatedesc));
    samplerstatedesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerstatedesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerstatedesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    samplerstatedesc.BorderColor[0] = 1.0f;
    samplerstatedesc.BorderColor[1] = 1.0f;
    samplerstatedesc.BorderColor[2] = 1.0f;
    samplerstatedesc.BorderColor[3] = 1.0f;

    samplerstatedesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerstatedesc.MaxLOD = std::numeric_limits<float>::max();
    samplerstatedesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
    samplerstatedesc.MaxAnisotropy = 1;

    HRESULT r = device->CreateSamplerState(&samplerstatedesc, &this->_samplerstate);
    if (FAILED(r))
    {
        throw std::runtime_error("Failed to create a sampler state!");
    }
}

SamplerState::SamplerState(ID3D11Device* device, const SamplerStateDescription& desc)
{
    _samplerstate = nullptr;

    D3D11_SAMPLER_DESC desc_dx;
    memset(&desc_dx, 0, sizeof(D3D11_SAMPLER_DESC));

    desc_dx.Filter = (D3D11_FILTER)desc.Filter;

    desc_dx.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressU;
    desc_dx.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressV;
    desc_dx.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressW;
    desc_dx.MipLODBias = desc.MipLODBias;
    desc_dx.MaxAnisotropy = desc.MaxAnisotropy;
    desc_dx.ComparisonFunc = (D3D11_COMPARISON_FUNC)desc.ComparisonFunc;

    desc_dx.BorderColor[0] = desc.BorderColor.R;
    desc_dx.BorderColor[1] = desc.BorderColor.G;
    desc_dx.BorderColor[2] = desc.BorderColor.B;
    desc_dx.BorderColor[3] = desc.BorderColor.A;

    desc_dx.MinLOD = desc.MinLOD;
    desc_dx.MaxLOD = desc.MaxLOD;

    HRESULT r = device->CreateSamplerState(&desc_dx, &this->_samplerstate);
    if (FAILED(r))
    {
        throw std::runtime_error("Failed to create a sampler state!");
    }
}

ID3D11SamplerState* SamplerState::GetCreatedSamplerState() const noexcept
{
    return this->_samplerstate;
}

void SamplerState::SetSamplerVertexShader(ID3D11DeviceContext* context)
{
    context->VSSetSamplers(0, 1, &this->_samplerstate);
}

void SamplerState::SetSamplerPixelShader(ID3D11DeviceContext* context)
{
    context->PSSetSamplers(0, 1, &this->_samplerstate);
}

void SamplerState::SetSamplerGeometryShader(ID3D11DeviceContext* context)
{
    context->GSSetSamplers(0, 1, &this->_samplerstate);
}

void SamplerState::SetSamplerDomainShader(ID3D11DeviceContext* context)
{
    context->DSSetSamplers(0, 1, &this->_samplerstate);
}

void SamplerState::SetSamplerHullShader(ID3D11DeviceContext* context)
{
    context->HSSetSamplers(0, 1, &this->_samplerstate);
}

SamplerState::~SamplerState()
{
    if (this->_samplerstate != nullptr) this->_samplerstate->Release();
}

#endif