/*

*/
#include "map.h"
#include <iostream>
#include "TinyXML/tinyxml.h"// TinyXML відкрита бібліотека для роботи з tmx (TiledMapEditor) файлами xml формату



int Object::GetPropertyInt(string name)
{
	return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(string name)
{
	return strtod(properties[name].c_str(), NULL);
}

string Object::GetPropertyString(string name)
{
	return properties[name];
}


bool Level::LoadFromFile(string filename)
{
	TiXmlDocument levelFile(filename.c_str());

	// Загружаем XML-карту
	if (!levelFile.LoadFile())
	{
		cout << "Loading level \"" << filename << "\" failed." << endl;
		return false;
	}

	// Работаем с контейнером map
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	// Пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	TiXmlElement* image;
	image = map->FirstChildElement("tileset");
	string imagepath = image->Attribute("source");
	imagepath.erase(imagepath.end() - 4, imagepath.end());
	cout << imagepath << endl;
	// Пытаемся загрузить тайлсет
	sf::Image img;

	if (!img.loadFromFile("maps/" + imagepath + ".png"))
	{
		cout << "Failed to load tile sheet." << endl;
		return false;
	}

	// Очищаем карту от света (109, 159, 185)
	// Вообще-то в тайлсете может быть фон любого цвета, но я не нашел решения, как 16-ричную строку
	// вроде "6d9fb9" преобразовать в цвет
	img.createMaskFromColor(Color(255, 255, 255));
	// Грузим текстуру из изображения
	tilesetImage.loadFromImage(img);
	// Расплывчатость запрещена
	tilesetImage.setSmooth(false);

	// Получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// Вектор из прямоугольников изображений (TextureRect)
	vector<Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}
	}
	// Работа со слоями
	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		// Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		// Контейнер <data>
		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			cout << "Bad map. No layer information found." << endl;
		}

		// Контейнер <tile> - описание тайлов каждого слоя
		TiXmlElement* tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			cout << "Bad map. No tile information found." << endl;
			return false;
		}

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			// Устанавливаем TextureRect каждого тайла
			if (subRectToUse >= 0)
			{
				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
				{
					y = 0;
				}
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	// Работа с объектами
	TiXmlElement* objectGroupElement;

	// Если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			// Контейнер <object>
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				// Получаем все данные - тип, имя, позиция, etc
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					//cout << objectElement->Attribute("id") << endl;
					width = subRects[atoi(objectElement->Attribute("id")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("id")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("id")) - firstTileID]);
				}

				// Экземпляр объекта
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;

				Rect <int> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;

				// "Переменные" объекта
				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							string propertyName = prop->Attribute("name");
							string propertyValue = prop->Attribute("value");

							object.properties[propertyName] = propertyValue;

							prop = prop->NextSiblingElement("property");
						}
					}
				}

				// Пихаем объект в вектор
				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		cout << "No object layers found..." << endl;
	}

	return true;
}

Object Level::GetObject(string name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].name == name)
		{
			return objects[i];
		}
	}
}

vector<Object> Level::GetObjects(string name)
{
	vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].name == name)
		{
			vec.push_back(objects[i]);
		}
	}
	return vec;
}

Vector2i Level::GetTileSize()
{
	return Vector2i(tileWidth, tileHeight);
}

vector<Object> Level::GetAllObjects()
{
	return objects;
};


void Level::Draw(RenderWindow& window)
{
	for (int layer = 0; layer < layers.size(); layer++)
	{
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			window.draw(layers[layer].tiles[tile]);
		}
	}
}
/**/