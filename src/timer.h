#ifndef TIMER_H
#define TIMER_H
namespace engine{
	/**
	 * This class was taken from the LazyFoo SDL tutorial(http://lazyfoo.net/SDL_tutorials/), 
	 * we did not ask permission to use this, 
	 * however it is merely a help class which we didn't want to come up with on our own.
	 */
	class Timer{
		private:
		int startTicks;
		int pausedTicks;

		bool paused;
		bool started;

		public:
		Timer();

		void start();
		void reset();
		void stop();
		void pause();
		void unpause();

		int get_ticks();

		bool is_started();
		bool is_paused();
	};
}
#endif