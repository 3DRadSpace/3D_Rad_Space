#include "Timer.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

Timer::Timer(
	const std::string& name,
	bool enabled,
	double interval,
	unsigned repeatCount,
	const Reflection::Event& event
) : IObject(name, enabled),
	Interval(interval),
	RepeatCount(repeatCount),
	Event(event),
	_elapsedTime(0.0),
	_ticks(0)
{
}

void Timer::Initialize()
{
	ResetTimer();
}

void Timer::Update()
{
	if (!Enabled) return;

	auto game = static_cast<Game*>(_game);
	auto dt = game->Update_dt;

	_elapsedTime += dt;

	if (_elapsedTime > Interval)
	{
		Event.InvokeAllReturnless();
		_elapsedTime = 0.0;
		_ticks++;

		if (_ticks > RepeatCount && RepeatCount != 0)
		{
			Enabled = false;
		}
	}
}

void Timer::ResetTimer() noexcept
{
	_elapsedTime = 0.0;
	_ticks = 0;
}

double Timer::GetRemainingTime() const noexcept
{
	return Interval - _elapsedTime;
}

unsigned Timer::GetRemainingTicks() const noexcept
{
	if (RepeatCount == 0) return 0;
	return RepeatCount - _ticks;
}

Reflection::UUID Timer::GetUUID() const noexcept
{
	// {2A1521AE-A905-48A0-8671-D2AC6B09B30D}
	return { 0x2a1521ae, 0xa905, 0x48a0, { 0x86, 0x71, 0xd2, 0xac, 0x6b, 0x9, 0xb3, 0xd } };
}

void Timer::Load()
{
}

void Timer::Load(const std::filesystem::path& path)
{
	(void)path;
}

REFL_BEGIN(Timer, "Timer", "Events", "Event object that executes an event at a specified interval, for a specified number of times")
	REFL_FIELD(Timer, std::string, Name, "Name", "Timer", "Object name")
	REFL_FIELD(Timer, bool, Enabled, "Enabled", true, "Is the timer running?")
	REFL_FIELD(Timer, double, Interval, "Interval", 1.0, "Timer interval expressed in seconds")
	REFL_FIELD(Timer, unsigned, RepeatCount, "RepeatCount", 0, "How many times the timer executes. 0 = infinite counts.")
	REFL_FIELD(Timer, Reflection::Event, Event, "Event", {}, "Executes each time the timer reaches the interval. Return value is ignored.")
REFL_END