#include <string>
//#include <sdl.h>

namespace engine{
	class Sprite {
		//SDL_Surface *image; // to be implemented
		int x, y;
		int w, h;
		
		Sprite(const Sprite& other){}
		const Sprite &operator=(const Sprite& other){}
		
	protected:
		Sprite(std::string filename);

	public:
		virtual ~Sprite();
		
		/**
		 * Runs every frame, change eventual movement of the sprite here.
		 */
		virtual void tick() = 0;
		
		/**
		 * Draw the sprite onto the screen.
		 */
		virtual void draw() const;
		
		/**
		 * Returns an approximate value for describing the location of the sprite on the screen.
		 * Used for efficiently calculating the collision detection
		 */
		int getHash() const;
		
		/**
		 * Calculates if this sprite is colliding with another sprite.
		 * Default collision is calculated with the size of the sprite, and does not calculate pixel collisions.
		 */
		virtual bool collidesWith(const Sprite*) const;
		
		/**
		 * The actions that should be performed if this sprite collides with anything.
		 */
		virtual void onCollision(const Sprite*) = 0;
	};
}