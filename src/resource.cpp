#include <string>
#include "resource.h"
#include "cconfig.h"

using namespace std;
namespace engine{
	map<string, Image*> Resource::loadedImages = map<string, Image*>();
	Image* Resource::loadImage(std::string filename){
		Image* result = NULL;

		if(loadedImages.find(filename) != loadedImages.end())
			result = loadedImages[filename];
		else{
			result = new Image((string)DATA_DIR + "/img/" + filename);
			loadedImages[filename] = result;
		}

		return result;
	}
}