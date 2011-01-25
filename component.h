
namespace engine {
	class Component {
		int m_x, m_y;

		Component(const Component &other){}
		const Component &operator=(const Component &other){}
		
	protected:
		Component(int x, int y) : m_x(x), m_y(y){}

	public:
		virtual ~Component();
		/**
		 * Draw the component onto the screen.
		 */
		virtual void draw() const;
	};
}