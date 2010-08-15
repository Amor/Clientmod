#include <game/client/component.hpp>

class MAPIMAGES : public COMPONENT
{	
	int textures[64];
	int entities_textures;
	int count;
public:
	MAPIMAGES();
	
	int get(int index) const { return textures[index]; }
	int get_entities();
	int num() const { return count; }

	virtual void on_mapload();
};

