#pragma once

#ifndef _ROCO_DSL_FSM_HPP_
#define _ROCO_DSL_FSM_HPP_

#include "../roco_ns.h"

_ROCO_BEGIN

// events
struct play;
struct open_close;
struct cd_detected;
struct pause;
struct stop;

template <class Derived>
class state_machine
{
protected:
	template <
		int CurrentState,
		class Event,
		int NextState,
		void (Derived::*action)(Event const&)
	>
		struct row
	{
		static constexpr int current_state = CurrentState;
		static constexpr int next_state = NextState;
		typedef Event event;
		typedef Derived fsm_t;

		static void execute(Derived& fsm, Event const& e)
		{
			(fsm.*action)(e);
		}
	};
};

class player : public state_machine<player>
{
private:
	enum states {
		Empty, Open, Stopped, Playing, Paused,
		initial_state = Empty
	};

	void start_playback(play const&);
};
_ROCO_END

#endif // _ROCO_DSL_FSM_HPP_