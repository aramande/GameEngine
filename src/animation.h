#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include "image.h"
#include "logger.h"
#include "resource.h"

namespace engine{
	struct Frame{
		Image* image;
		float delay;
		~Frame(){
			if(image != NULL){
				logger->printf("Unloading image(%p) from frame", image);
				Resource::unloadImage(image);
				image = NULL;
				delay = 0.0f;
			}
		}
	};
	class Animation{
		std::vector<Frame> frames;
		int frameCount;
		int currentFrame;
	public:
		Animation();
		~Animation();

		/**
		 * Set the number of frames. Make sure to fill out all the frames to
		 * avoid null pointers to images.
		 *
		 * @param length New limit for frames
		 */
		void setFrames(int length);

		/**
		 * Set an image to a frame index.
		 *
		 * @param index Frame number index
		 * @param image An image that should be shown this frame
		 * @param delay The time that should have passed since the last frame
		 *		was played in seconds.
		 */
		void setFrame(const int& index, Image* image, float delay=0.0f);
		const Frame& getFrame(const int& index) const;

		/**
		 * @return The index of the frame that is currently being shown.
		 */
		const int& getCurrentFrame() const;

	};
}

#endif
