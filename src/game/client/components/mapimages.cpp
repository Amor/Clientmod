#include <game/client/component.hpp>
#include <game/mapitems.hpp>

#include "mapimages.hpp"

MAPIMAGES::MAPIMAGES()
{
	count = 0;
	entities_textures = -1;
}

void MAPIMAGES::on_mapload()
{
	// unload all textures
	for(int i = 0; i < count; i++)
	{
		gfx_unload_texture(textures[i]);
		textures[i] = -1;
	}
	count = 0;

	int start;
	map_get_type(MAPITEMTYPE_IMAGE, &start, &count);
	
	// load new textures
	for(int i = 0; i < count; i++)
	{
		textures[i] = 0;
		
		MAPITEM_IMAGE *img = (MAPITEM_IMAGE *)map_get_item(start+i, 0, 0);
		if(img->external)
		{
			char buf[256];
			char *name = (char *)map_get_data(img->image_name);
			str_format(buf, sizeof(buf), "mapres/%s.png", name);
			textures[i] = gfx_load_texture(buf, IMG_AUTO, 0);
		}
		else
		{
			void *data = map_get_data(img->image_data);
			textures[i] = gfx_load_texture_raw(img->width, img->height, IMG_RGBA, data, IMG_RGBA, 0);
			map_unload_data(img->image_data);
		}
	}
}

int MAPIMAGES::get_entities()
{
	if(entities_textures == -1)
	{
		char entities_path[256];
		str_format(entities_path, sizeof(entities_path), "editor/entities_clear.png");
		entities_textures = gfx_load_texture(entities_path, IMG_AUTO, 0); // Dunedune:  first try to load the clear entities
		if(entities_textures == -1)
			entities_textures = gfx_load_texture("editor/entities.png", IMG_AUTO, 0); // Failed : load the std entities
	}
	return entities_textures;
}


