#include "animation.h"
#include "badarg.h"

namespace engine{
	Animation::Animation() : currentFrame(0), frameCount(1){
		logger->print("Adding animation");
		frames.resize(1);
	}
	Animation::~Animation(){
	//	frames.clear();
	}

	void Animation::setFrames(int length){
		frameCount = length;
		frames.resize(frameCount);
	}

	void Animation::setFrame(const int& index, Image* image, float delay){
		if(index >= frameCount)
			throw bad_arg("Frame index out of range: " + toStr(frameCount) + "<" + toStr(index));
		if(!image)
			throw bad_arg("Image null pointer exception");
		logger->printf("Setting frame to %p, with delay %f", image, delay);
		frames[index].image = image;
		frames[index].delay = delay;
	}
	
	const Frame& Animation::getFrame(const int& index) const{
		if(index >= frameCount)
			throw bad_arg("Frame index out of range: " + toStr(frameCount) + "<" + toStr(index));
		return frames[index];
	}
	
	const int& Animation::getCurrentFrame() const{
		return currentFrame;
	}
}
