#ifndef IGAME_INCLUDED
#define IGAME_INCLUDED

#include "../Core/ICore.h"
#include "../Core/Math.h"

typedef unsigned int uint;

class ICell;
class IMap;

/**
* @brief Ядро игры
* @detailed Через этот класс происходят взаимодействия между всеми игровыми объектами
*/
class IGame {
public:
    IGame(ICore *__core) {core=__core;getCore()->log("Game object create");};
    virtual ~IGame() {getCore()->log("Game object destroy");}
    ICore *getCore() {return core;};
private:
    ICore *core;
};

/**
* @brief Карта уровня
* @detailed Класс хранит ландшафт игрового уровня а так же занимается его отрисовкой
*/
class IMap {
public:
    IMap(IGame *__game) {game=__game;};
    IGame* getGame() {return game;};
    virtual void resize(uint newWidth, uint newHeight) = 0;
    virtual uint getWidth()=0;
    virtual uint getHeight()=0;
    virtual ICell* getCell(uint cx, uint cy)=0;
private:
    IGame *game;
    virtual float getCellSize()=0;
};

/**
* @brief Тип ячейки игрового уровня
* @detailed Может быть водой, землей или пустым местом
*/
enum CellType {
    none,   //Обрыв—будет как падающая вода
    water,  //Вода, для плавания
    block   //блоки для сухопутных крыс
};

/**
* @brief Ячейка игрового уровня
* @detailed Минимальная единица ландшафта уровня
*/
class ICell {
public:
    virtual CellType getCellType()=0;
    virtual void setCellType(CellType __cellType)=0;
};

/**
* @brief Игровой объект
*/
class IGameObject {
public:
    virtual bool isSolid(){return false;}
    //Позиция объекта
    Vector3d *getPosition() {return &position;}
    //момент скорости
    Vector3d *getMoment() {return &moment;}
protected:
    Vector3d position;
    Vector3d moment;
};

/**
* @brief Форма объекта
* @detailed Форма объекта для вычисления столкновений
*/
enum Shape {
    shRectangle,
    shEllipse
};

/**
* @brief Типы повреждения
*/
enum DamageType{
    dtStrike,   //Удар
    dtShot,     //Выстрел
    dtCut,      //Режущий
    dtFire,     //Огонь
    dtLight,    //Свет
    dtElectric, //Электричество
    dtIce,      //Лед
    dtPoison    //Яд
};

/**
* @brief Объемный игровой объект
* @detailed Игровой объект который учавствует в просчете столкновений
*/
class ISolidGameObject: public IGameObject {
public:
    bool isSolid(){return true;}
    //радиус или половина ширины объекта
    float getSize() {return size;}
    //форма объекта
    Shape getShape() {return shape;}
    //Группа, к которой относится объект
    int getObjectGroup() {return objectGroup;}
    //группа объекта для вычисления столкновений
    int getCollisionGroup() {return collisionGroup;}
    //нанести повреждение
    virtual float demage(float amount, DamageType _type) {return 0;}
protected:
    float size;
    Shape shape;
    int objectGroup;
    int collisionGroup;
};
#endif // IGAME_INCLUDED
