#include "pch.h"
#include "PerceptualHash.hpp"
#include <bit>
#include <d3d11.h>
#include <wrl/client.h>
#include <directxtk/WICTextureLoader.h>
#include <wincodec.h>
#include <cmath>

using Microsoft::WRL::ComPtr;

namespace Engine3DRadSpace::Testing
{
	PerceptualHash::Hash PerceptualHash::ComputeHash(const std::filesystem::path& imagePath)
	{
		auto resized = LoadAndResize(imagePath);
		return ComputeDHash(resized);
	}

	unsigned PerceptualHash::HammingDistance(Hash hash1, Hash hash2)
	{
		return static_cast<unsigned>(std::popcount(hash1 ^ hash2));
	}

	bool PerceptualHash::AreImagesSimilar(const std::filesystem::path& imagePath1,
										   const std::filesystem::path& imagePath2,
										   unsigned threshold)
	{
		Hash hash1 = ComputeHash(imagePath1);
		Hash hash2 = ComputeHash(imagePath2);
		return HammingDistance(hash1, hash2) <= threshold;
	}

	PerceptualHash::ImageData PerceptualHash::LoadAndResize(const std::filesystem::path& imagePath, size_t targetWidth, size_t targetHeight)
	{
		// Initialize COM for WIC
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		// Create WIC factory
		ComPtr<IWICImagingFactory> wicFactory;
		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&wicFactory)
		);
		if (FAILED(hr)) throw std::runtime_error("Failed to create WIC factory");

		// Load the image
		ComPtr<IWICBitmapDecoder> decoder;
		hr = wicFactory->CreateDecoderFromFilename(
			imagePath.wstring().c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&decoder
		);
		if (FAILED(hr)) throw std::runtime_error("Failed to load image: " + imagePath.string());

		ComPtr<IWICBitmapFrameDecode> frame;
		hr = decoder->GetFrame(0, &frame);
		if (FAILED(hr)) throw std::runtime_error("Failed to get image frame");

		// Convert to RGBA format
		ComPtr<IWICFormatConverter> converter;
		hr = wicFactory->CreateFormatConverter(&converter);
		if (FAILED(hr)) throw std::runtime_error("Failed to create format converter");

		hr = converter->Initialize(
			frame.Get(),
			GUID_WICPixelFormat32bppRGBA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0,
			WICBitmapPaletteTypeCustom
		);
		if (FAILED(hr)) throw std::runtime_error("Failed to initialize format converter");

		// Get original dimensions
		UINT srcWidth, srcHeight;
		hr = converter->GetSize(&srcWidth, &srcHeight);
		if (FAILED(hr)) throw std::runtime_error("Failed to get image size");

		// Read original image data
		size_t srcRowPitch = srcWidth * 4; // 4 bytes per pixel (RGBA)
		size_t srcImageSize = srcRowPitch * srcHeight;
		auto srcPixels = std::make_unique<uint8_t[]>(srcImageSize);

		hr = converter->CopyPixels(
			nullptr,
			static_cast<UINT>(srcRowPitch),
			static_cast<UINT>(srcImageSize),
			srcPixels.get()
		);
		if (FAILED(hr)) throw std::runtime_error("Failed to copy pixels");

		// Resize to target dimensions
		size_t dstRowPitch = targetWidth * 4;
		size_t dstImageSize = dstRowPitch * targetHeight;
		auto dstPixels = std::make_unique<uint8_t[]>(dstImageSize);

		BilinearResize(
			srcPixels.get(), srcWidth, srcHeight, srcRowPitch,
			dstPixels.get(), targetWidth, targetHeight, dstRowPitch
		);

		ImageData result;
		result.pixels = std::move(dstPixels);
		result.width = targetWidth;
		result.height = targetHeight;
		result.rowPitch = dstRowPitch;

		return result;
	}

	void PerceptualHash::BilinearResize(const uint8_t* src, size_t srcWidth, size_t srcHeight, size_t srcPitch,
										uint8_t* dst, size_t dstWidth, size_t dstHeight, size_t dstPitch)
	{
		float xRatio = static_cast<float>(srcWidth) / static_cast<float>(dstWidth);
		float yRatio = static_cast<float>(srcHeight) / static_cast<float>(dstHeight);

		for (size_t y = 0; y < dstHeight; ++y)
		{
			for (size_t x = 0; x < dstWidth; ++x)
			{
				float srcX = x * xRatio;
				float srcY = y * yRatio;

				size_t x1 = static_cast<size_t>(srcX);
				size_t y1 = static_cast<size_t>(srcY);
				size_t x2 = (x1 + 1 < srcWidth) ? (x1 + 1) : (srcWidth - 1);
				size_t y2 = (y1 + 1 < srcHeight) ? (y1 + 1) : (srcHeight - 1);

				float xWeight = srcX - x1;
				float yWeight = srcY - y1;

				// Bilinear interpolation for each channel
				for (size_t c = 0; c < 4; ++c) // RGBA
				{
					float p1 = src[y1 * srcPitch + x1 * 4 + c];
					float p2 = src[y1 * srcPitch + x2 * 4 + c];
					float p3 = src[y2 * srcPitch + x1 * 4 + c];
					float p4 = src[y2 * srcPitch + x2 * 4 + c];

					float top = p1 * (1.0f - xWeight) + p2 * xWeight;
					float bottom = p3 * (1.0f - xWeight) + p4 * xWeight;
					float value = top * (1.0f - yWeight) + bottom * yWeight;

					dst[y * dstPitch + x * 4 + c] = static_cast<uint8_t>(value);
				}
			}
		}
	}

	PerceptualHash::Hash PerceptualHash::ComputeDHash(const ImageData& resizedImage)
	{
		// dHash algorithm: compare adjacent pixels in each row
		// Image should be 9x8 pixels (9 wide for 8 comparisons per row)
		if (resizedImage.width != 9 || resizedImage.height != 8)
			throw std::runtime_error("Image must be 9x8 for dHash computation");

		Hash hash = 0;
		const uint8_t* pixels = resizedImage.pixels.get();
		size_t rowPitch = resizedImage.rowPitch;

		// For each row, compare adjacent pixels
		for (size_t y = 0; y < 8; ++y)
		{
			for (size_t x = 0; x < 8; ++x)
			{
				// Get grayscale values for current and next pixel
				// RGBA format: offset = (y * rowPitch) + (x * 4)
				size_t offset1 = (y * rowPitch) + (x * 4);
				size_t offset2 = (y * rowPitch) + ((x + 1) * 4);

				// Convert to grayscale using luminance formula
				uint8_t gray1 = static_cast<uint8_t>(
					0.299f * pixels[offset1] +     // R
					0.587f * pixels[offset1 + 1] + // G
					0.114f * pixels[offset1 + 2]   // B
				);
				uint8_t gray2 = static_cast<uint8_t>(
					0.299f * pixels[offset2] +     // R
					0.587f * pixels[offset2 + 1] + // G
					0.114f * pixels[offset2 + 2]   // B
				);

				// Set bit if left pixel is brighter than right pixel
				size_t bitIndex = y * 8 + x;
				if (gray1 > gray2)
				{
					hash |= (1ULL << bitIndex);
				}
			}
		}

		return hash;
	}
}
