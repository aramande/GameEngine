
namespace engine {
	class Gui {
		int x, y;

		Gui(const Gui &other){}
		const Gui &operator=(const Gui &other){}
		
	protected:
		Gui();

	public:
		~Gui();
		/**
		 * Draw all the components onto the screen.
		 */
		void draw() const;
	};
}