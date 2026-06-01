#pragma once
#include <cstdint>
#include <vector>
#include <filesystem>
#include <memory>

namespace Engine3DRadSpace::Testing
{
	/// <summary>
	/// Perceptual hash using dHash (difference hash) algorithm.
	/// Compares structural similarity between images regardless of minor pixel differences.
	/// </summary>
	class PerceptualHash
	{
	public:
		using Hash = uint64_t;

		/// <summary>
		/// Computes perceptual hash for an image file.
		/// </summary>
		/// <param name="imagePath">Path to the image file</param>
		/// <returns>64-bit perceptual hash</returns>
		static Hash ComputeHash(const std::filesystem::path& imagePath);

		/// <summary>
		/// Calculates Hamming distance between two hashes (number of differing bits).
		/// Lower distance = more similar images.
		/// </summary>
		/// <param name="hash1">First hash</param>
		/// <param name="hash2">Second hash</param>
		/// <returns>Hamming distance (0-64)</returns>
		static unsigned HammingDistance(Hash hash1, Hash hash2);

		/// <summary>
		/// Checks if two images are perceptually similar.
		/// </summary>
		/// <param name="imagePath1">Path to first image</param>
		/// <param name="imagePath2">Path to second image</param>
		/// <param name="threshold">Maximum allowed Hamming distance (default: 5, typically 0-10 for similar images)</param>
		/// <returns>True if images are similar within threshold</returns>
		static bool AreImagesSimilar(const std::filesystem::path& imagePath1, 
									  const std::filesystem::path& imagePath2, 
									  unsigned threshold = 5);

	private:
		struct ImageData
		{
			std::unique_ptr<uint8_t[]> pixels;
			size_t width;
			size_t height;
			size_t rowPitch;
		};

		static ImageData LoadAndResize(const std::filesystem::path& imagePath, size_t targetWidth = 9, size_t targetHeight = 8);
		static Hash ComputeDHash(const ImageData& resizedImage);
		static void BilinearResize(const uint8_t* src, size_t srcWidth, size_t srcHeight, size_t srcPitch,
								   uint8_t* dst, size_t dstWidth, size_t dstHeight, size_t dstPitch);
	};
}
