#ifndef FONT_H
#define FONT_H

#include <string>
#include "sdl.h"
#include "resource.h"

namespace engine{
	class Font : public Resource{
		friend class ResourceParser;
		TTF_Font* font;
		int size;
		std::string path, filename;
		bool final;

		void setSize(int size);
		void setFile(std::string path, std::string filename);
		void finalize();

		Font(const Font& other){}
		Font operator=(const Font& other){}
		~Font();

	private:
		Font(std::string name);
	public:
		std::string getFilename() const;
		TTF_Font* getTTF() const;
	};
}

#endif
