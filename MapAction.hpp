#ifndef MAPACTION_HPP
#define MAPACTION_HPP

class MapAction {
    private:
        int id;
        int x;
        int y;
        char icon;
        char key;
        char type;
    public:
        MapAction(int, int, int, char, char, char, Direction);
        int getId();
        int getX();
        int getY();
        char getIcon();
        char getKey();
        char getType();
};

#endif
