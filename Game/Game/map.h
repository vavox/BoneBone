/*
Заголовочний файл мапи
*/
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace sf;

struct Object
{
    int GetPropertyInt(string name);
    float GetPropertyFloat(string name);
    string GetPropertyString(string name);

    string name;
    string type;
    Rect<int> rect;
    map<string, string> properties;

    Sprite sprite;
};

struct Layer
{
    int opacity;
    vector<Sprite> tiles;
};

class Level
{
public: 
    bool LoadFromFile(string filename);
    Object GetObject(string name);
    vector<Object> GetObjects(string name);
    void Draw(RenderWindow& window);
    Vector2i GetTileSize();
    vector<Object> GetAllObjects();
private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    Rect<float> drawingBounds;
    Texture tilesetImage;
    vector<Object> objects;
    vector<Layer> layers;
};
/**/