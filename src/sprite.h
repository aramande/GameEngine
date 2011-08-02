#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "sdl.h"
#include "image.h"
#include "rectangle.h"
#include "resource.h"

namespace engine{
	class Sprite {
		Image* image;
		Rectangle* rect;

		Sprite(const Sprite& other){}
		const Sprite &operator=(const Sprite& other){}
		typedef void(*Func)(const Sprite*);

	 public:
		Sprite(Image* image, int x=0, int y=0);
		virtual ~Sprite();

		/**
		 * Runs every frame, change eventual movement of the sprite here.
		 */
		virtual void tick();

		void repaint() const;
		/**
		 * Draw the sprite onto the mainScreen.
		 */
		virtual void draw() const;

		/**
		 * Returns an approximate value for describing the location of the sprite on the mainScreen.
		 * Used for efficiently calculating the collision detection
		 */
		int getHash() const;

		int getX();
		
		int getY();
		
		int getWidth();

		int getHeight();

		Rectangle* getRectangle() const;

		/**
		 * Moves the sprite across the mainScreen relative to the sprite current
		 * position.
		 */
		void translate(int x, int y);

		/**
		 * Moves the sprite to an exact position on the mainScreen. If we make
		 * anything like a viewport, this is a dangerous function to have.
		 */
		void moveTo(int x, int y);

		/**
		 * Resizes the surface to the new width and height, if this is smaller
		 * than the image provided in the filename, the image will be cropped.
		 */
		void resize(int w, int h);

		/**
		 * Calculates if this sprite is colliding with another sprite.
		 * Default collision is calculated with the size of the sprite, and does not calculate pixel collisions.
		 */
		virtual bool collidesWith(const Sprite*) const;

		/**
		 * The function that should be called if this sprite collides with anything.
		 * Expects a functionpointer to a function that takes a const Sprite*.
		 * The sprite pointer will contain the object this sprite collided with.
		 */
		virtual void onCollision(Func action);
	};
}

#endif
