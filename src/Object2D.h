#pragma once

#include <utility>
#include <vector>
#include <cmath>
#include "Point2D.h"
#include "Idrawable.h"
#include "settings.h"


class Object2D : virtual public Idrawable {
protected:
    size_t oid;
    std::vector<Point2D> v_points2D;

    Point2D p_position;
    Point2D p_velocity;

    double d_height = 1;
    bool b_isMirror = false;

    sf::Texture T_texture;
    std::string s_texture;
    bool texture_loaded = false;
public:
    Object2D(Point2D position = {0, 0}, std::vector<Point2D> points = {}, double height = 1, std::string texture = WALL_TEXTURE, Point2D velocity = {0, 0})
    : p_position(position), v_points2D(points), p_velocity(velocity),  s_texture(std::move(texture)), d_height(height) {}

    Object2D(const Object2D& object2D) { // copy constructor
        v_points2D = object2D.v_points2D;
        p_position = object2D.p_position;
        p_velocity = object2D.p_velocity;
        d_height = object2D.d_height;
        b_isMirror = object2D.b_isMirror;
        T_texture = object2D.T_texture;
        s_texture = object2D.s_texture;
        texture_loaded = object2D.texture_loaded;
    }

    const double x() { return p_position.x; }
    const double y() { return p_position.y; }

    const Point2D& getPosition() const { return p_position; }
    void setPosition(Point2D position) { p_position = position; }

    void shift(Point2D vector) { p_position += vector; }

    std::vector<Point2D>& nodes() { return v_points2D; }

    static bool segments_crossing(std::pair<Point2D, Point2D> segment1, std::pair<Point2D, Point2D> segment2, Point2D& point);

    void setId(size_t id) { oid = id; }
    size_t getId() const { return oid; }

    Point2D position() const { return p_position; }

    bool isMirror () const { return b_isMirror; }
    void makeMirror() { b_isMirror = true; }
    void makeItNotMirror() {b_isMirror = false; }

    void draw(sf::RenderWindow& window) override;

    double height() const { return d_height; }

    sf::Texture& loadTexture() {
        if(texture_loaded) return T_texture;
        texture_loaded = true;
        if (!T_texture.loadFromFile(s_texture)) {
            texture_loaded = false;
        }
        T_texture.setRepeated(true);
        return T_texture;
    }

    virtual int type() { return 0; }
    void setPoints2D (std::vector<Point2D> points2D) {
        v_points2D = std::move(points2D);
    }
};
