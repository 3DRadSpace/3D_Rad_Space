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

		virtual std::string What() const;
		const char* what() const override;

		const std::stacktrace& GetStacktrace() const noexcept;

		~Exception() override = default;
	};
#pragma warning(pop)
}

