#ifndef EVENT_H
#define EVENT_H

namespace engine{
	class Event{
	private:
		int time;
	public:
		Event(int timeSinceLastFrame) : time(timeSinceLastFrame){}
		virtual ~Event(){}
		int getTimeSinceLastFrame() const{
			return time;
		}
	};
}

#endif