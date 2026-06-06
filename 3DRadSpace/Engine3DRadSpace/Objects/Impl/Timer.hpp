#pragma once
#include "../IObject.hpp"
#include "../../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents an event object that executes an event at a specified interval, for a specified number of times.
	/// </summary>
	class Timer : public IObject
	{
	protected:
		double _elapsedTime = 0.0f;
		unsigned _ticks = 0;
	public:
		/// <summary>
		/// Constructs an timer object.
		/// </summary>
		/// <param name="name">Object name</param>
		/// <param name="enabled">Is the timer running?</param>
		/// <param name="interval">Timer interval expressed in seconds</param>
		/// <param name="repeatCount">How many times the timer executes. 0 = infinite counts.</param>
		/// <param name="event">Event to execute when the timer reaches the interval</param>
		Timer(
			const std::string& name = "Timer",
			bool enabled = true,
			double interval = 1.0,
			unsigned repeatCount = 0,
			const Reflection::Event& event = {}
		);
		
		Timer(Timer&&) noexcept = default;
		Timer& operator=(Timer&&) noexcept = default;

		/// <summary>
		/// Timer interval expressed in seconds.
		/// </summary>
		double Interval = 1.0;
		/// <summary>
		/// How many times the timer executes.
		/// 
		/// 0 = infinite counts.
		/// </summary>
		unsigned RepeatCount = 0;

		/// <summary>
		/// Executes each time the timer reaches the interval. Return value is ignored.
		/// </summary>
		Reflection::Event Event;

		/// <summary>
		/// Calls ResetTimer().
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">Ignored.</param>
		void Load(const std::filesystem::path& path) override;

		/// <summary>
		/// Count mechanism.
		/// </summary>
		void Update() override;

		/// <summary>
		/// Returns remaining time.
		/// </summary>
		/// <returns>Interval - _elapsedTime</returns>
		double GetRemainingTime() const noexcept;
		/// <summary>
		/// Returns remaining ticks.
		/// </summary>
		/// <returns>RepeatCoun
		unsigned GetRemainingTicks() const noexcept;
		/// <summary>
		/// Resets the timer's elapsed time and tick count.
		/// </summary>
		void ResetTimer() noexcept;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Timer() override = default;
	};
}