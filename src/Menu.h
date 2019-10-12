#pragma once

#include <memory>

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

#include "Utils.h"

class Menu
{
public:
    Menu();
    virtual ~Menu() {}
    virtual void up() = 0;
    virtual void right() = 0;
    virtual void down() = 0;
    virtual void left() = 0;

protected:
    Menu(std::shared_ptr<LiquidCrystal_I2C> lcd)
    {
        LiquidMenu liquidMenu(*lcd);
        liquidMenu.init();
        menu = std::make_shared<LiquidMenu>(liquidMenu);
    }
    std::shared_ptr<LiquidMenu> menu;
};

class StaticMenu : public Menu
{
public:
    StaticMenu(std::shared_ptr<LiquidCrystal_I2C> lcd);
    void up();
    void right();
    void down();
    void left();
};