#ifndef BUTTONITEM_HPP
#define BUTTONITEM_HPP

#include <queue>

#include "MapItem.hpp"

class ButtonItem: public MapItem
{
    private:
        bool on;
    public:
        ButtonItem(int, int, std::queue<MapAction*>*);
        virtual ItemType getType();
        virtual bool isSolid(MapItem*);
        void setOn(bool);
        bool isOn();
};

#endif
