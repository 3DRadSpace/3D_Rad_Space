#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
#pragma warning(push)
#pragma warning(disable:4275)
	/// <summary>
	/// Replaces std::exception. Also contains a stacktrace of where the exception was thrown.
	/// </summary>
	class E3DRSP_LOGGING_EXPORT Exception : public std::exception
	{
	protected:
		std::string _str;
		std::stacktrace _stacktrace;
	public:
		explicit Exception(const std::string &err);

		Exception() = default;
		Exception(Exception&) = default;
		Exception(Exception&&) = default;

		/// <summary>
		///	Same as std::exception::what(), but returns a std::string instead of const char*.
		/// </summary>
		/// <returns></returns>
		virtual std::string What() const;
		/// <summary>
		/// Returns a C-style string describing the general cause of the current error.
		/// </summary>
		/// <returns>C-style string describing the general cause of the current error</returns>
		const char* what() const override;
		/// <summary>
		/// Gets the stacktrace of where the exception was thrown.
		/// </summary>
		/// <returns>Stacktrace of where the exception was thrown</returns>
		const std::stacktrace& GetStacktrace() const noexcept;

		~Exception() override = default;
	};
#pragma warning(pop)
}

