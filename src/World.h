#pragma once

#include "Object2D.h"
#include <string>
#include <map>

class World : virtual public Idrawable {
private:
    //std::map<std::string, Object2D&> map_objects;
    std::vector<Object2D*> objects;
    size_t nextOid = 0;

    double d_length = 0;
    double d_width = 0;

    sf::Texture T_sky_texture;
    sf::Texture T_floor_texture;
    bool sky_texture_loaded = false;
    bool floor_texture_loaded = false;
    std::string s_sky_texture;
    std::string s_floor_texture;
	sf::Sprite S_floor;

public:
    World(double length, double width, std::string sky_texture = SKY_TEXTURE, std::string floor_texture = FLOOR_TEXTURE) : d_length(length), d_width(width), s_sky_texture(sky_texture), s_floor_texture(floor_texture)
    {
        S_floor.setTexture(floorTexture());
    }

    sf::Sprite& floor() {
        return S_floor;
    }

    //Add object and return objectId
    size_t addObject2D(Object2D& object)
    {
        object.setId(nextOid);
        objects.push_back(&object);
        return nextOid++;
    }

    Object2D* findObject2D(size_t id) const
    {
        auto res = std::lower_bound(objects.begin(), objects.end(), id, [](const Object2D* obj, size_t id) {
            return obj->getId() < id;
        });
        if (res != objects.end()) {
            return *res;
        }
        return nullptr;
    }

    bool isExist(size_t id) const { return findObject2D(id) != nullptr; }

    //bool removeObject2D(std::string name) { return map_objects.erase(name) > 0; }

    Object2D* operator[](size_t id) const {
        return findObject2D(id);
    }

    double width() const { return d_width; }
    double length() const { return d_length; }

    void draw(sf::RenderWindow& window) override;

    const std::vector<Object2D*> getObjects() const {return objects;};

    const sf::Texture& skyTexture() {
        if(sky_texture_loaded) return T_sky_texture;
        sky_texture_loaded = true;
        if (!T_sky_texture.loadFromFile(s_sky_texture)) {
            sky_texture_loaded = false;
        }
        T_sky_texture.setRepeated(true);
        return T_sky_texture;
    }

    const sf::Texture& floorTexture() {
        if(floor_texture_loaded) return T_floor_texture;
        floor_texture_loaded = true;
        if (!T_floor_texture.loadFromFile(s_floor_texture)) {
            floor_texture_loaded = false;
        }
        T_floor_texture.setRepeated(true);
        return T_floor_texture;
    }
};
