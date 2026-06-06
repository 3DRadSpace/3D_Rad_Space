#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Audio
{
	class Sound;

	/// <summary>
	/// Represents a PCM audio buffer.
	/// </summary>
	class E3DRSP_AUDIO_EXPORT AudioBuffer
	{
	protected:
		std::unique_ptr<char[]> _buffer;
		int _channel = 0;
		int _sampleRate = 0;
		int _bps = 0;
		int _format = 0;
		int _size = 0;
	public:
		/// <summary>
		/// Constructs a AudioBuffer from specified arguments.
		/// </summary>
		/// <param name="buffer">PCM buffer</param>
		/// <param name="numChannels">Number of channels</param>
		/// <param name="sampleRate">Audio sample rate</param>
		/// <param name="bps">Beats per second</param>
		/// <param name="format">OpenAL format</param>
		/// <param name="size">Buffer size</param>
		AudioBuffer(char* buffer, int numChannels, int sampleRate, int bps, int format, int size);

		AudioBuffer(const AudioBuffer&) = delete;
		AudioBuffer(AudioBuffer&&) noexcept = default;

		AudioBuffer& operator=(const AudioBuffer&) = delete;
		AudioBuffer& operator=(AudioBuffer&&) noexcept = default;

		enum class WAVLoadError
		{
			None,
			CannotOpen,
			RIFFNotFound,
			NoFormatMarker,
			WrongFormatLength,
			NotPCM,
			NullSize,
			OutOfMemory
		};

		/// <summary>
		/// Loads a WAV file from the given path and returns an AudioBuffer instance.
		/// </summary>
		static std::expected<AudioBuffer, WAVLoadError> FromWAV(const std::filesystem::path& path);
		
		/// <summary>
		/// Type of loading error that could occur when loading an OGG file.
		/// </summary>
		enum class OGGLoadError
		{
			/// <summary>
			/// No error, loading succeeded.
			/// </summary>
			None,
			/// <summary>
			/// File is unreadable or does not exist.
			/// </summary>
			CannotOpen,
			/// <summary>
			/// File is not a valid OGG file.
			/// </summary>
			Invalid,
			/// <summary>
			/// OGG file is missing the "vorbis" info header.
			///	</summary>
			InfoFail,
			/// <summary>
			/// Not enough memory to allocate the PCM buffer.
			/// </summary>
			OutOfMemory,
		};
		
		/// <summary>
		/// Loads an OGG file from the given path and returns an AudioBuffer instance.
		/// </summary>
		/// <param name="path">Path to the OGG file</param>
		/// <returns>AudioBuffer instance or OGGLoadError</returns>
		static std::expected<AudioBuffer, OGGLoadError> FromOGG(const std::filesystem::path& path);

		~AudioBuffer() = default;

		friend class Sound;
	};
}