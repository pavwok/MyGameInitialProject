#include <SFML/Graphics.hpp> //исп библиотеки sfml графики
#include <cstdlib> //исп библиотеки для исп std
#include <windows.h> // исп библиотеки для работы в windows
#include <iostream> //исп стандартной библиотеки


using namespace sf; // ( это для подстраховки:] )

 sf::RenderWindow window; //задаем окно
 sf::CircleShape circle(50,4); //задаем квадрат
 sf::RectangleShape rectangle(sf::Vector2f(150,70)); // твердый прямоугольник
 sf::RectangleShape rectangleTele(sf::Vector2f(10,70));//телепортирующая фигура
 sf::RectangleShape rectangleTele2(sf::Vector2f(10,70));//2-я фигура для телепорта
 sf::CircleShape circle1(25,10); //исчезающий круг
 sf::CircleShape circle2(20,30); // двигающийся круг
 sf::Image image; //имя картинки
 sf::Texture texture; //текстурка
 sf::Sprite sprite;

 float speed = 0.1; //скорость персонажа
 float CurrentFrame = 0;
 int HeroDirection; //персонаж


int main()
{
//создание экрана
    window.create(sf::VideoMode(640,480),"Walking man");
window.setFramerateLimit(60);//кол-во кадр/сек


//===================================================================
    circle.setFillColor(sf::Color::Yellow); //цвет квадрата
    circle.setPosition(200,350); //радиус квадрата
    circle.rotate(45); // поворот фигуры ( если убрать, то будет ромб)

    rectangle.setFillColor(sf::Color::Cyan); // цвет тверд. прямоугольника
    rectangle.setPosition(200,200); //радиус прямоугольника

    circle1.setFillColor(sf::Color::Yellow); //цвет исч.круга
    circle1.setPosition(300,400); //радиус круга

    circle2.setFillColor(sf::Color::Red); //цвет двиг. круга
    circle2.setPosition(500,200); //радиус круга

//===================================================================
    image.loadFromFile("image.png");//путь к картинке с персонажем
    texture.loadFromImage(image);//преоброзование в текстуру
    sprite.setTexture(texture);//заключ текстуру в прямоугольник
    sprite.setPosition(50,50);  // радиус картинки
   sprite.setTextureRect(sf::IntRect(0,0,64,96)); //вырез из картинуи

//===================================================================
     rectangleTele.setFillColor(sf::Color::Green); //телепортирующая фигура
    rectangleTele.setPosition(100,100); // радиус

  rectangleTele2.setFillColor(sf::Color::Green); // 2-я фигура для телепорта
    rectangleTele2.setPosition(200,100); // радиус

//===================================================================
    sf::Clock clock; // добавление временного таймера

    while (window.isOpen()) // если открыто окно
    {
//засекаем время:
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

//===================================================================
//-------событие для окна:
   sf::Event event;//проверка окрытости окна
   while (window.pollEvent(event))
   {
//если нажать на кнопку закрыть:
       if (event.type == sf::Event::Closed)
        window.close();
   }

//===================================================================
//----события взаимодействия персонажа с объектами
   sf::FloatRect spriteBounds = sprite.getGlobalBounds();// изымаем данные персонажа
   sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();// изымаем данные прямоугольника
sf::FloatRect circle1Bounds = circle1.getGlobalBounds();// изымаем данные исч.круга
sf::FloatRect circle2Bounds = circle2.getGlobalBounds();// изымаем данные двиг. круга
sf::FloatRect circleBounds = circle.getGlobalBounds();//изымаем данные квадрата
sf::FloatRect Teleportation = rectangleTele.getGlobalBounds();//изымаем данные телепорта

//===================================================================
//------взаимодействие с прямоугольником
   if (spriteBounds.intersects(rectangleBounds))
    {
   // std:: cout << "collision"<< std::endl; //(эта строка для проверки)
       if (HeroDirection==0)
        sprite.move(speed*time,0); //отталкивание персонажа от прямоугольника вправо
       if (HeroDirection==2)
        sprite.move(-speed*time,0);//отталкивание персонажа от прямоугольника влево
        if (HeroDirection==3)
        sprite.move(0,speed*time);//отталкивание персонажа от прямоугольника вниз
        if (HeroDirection==4)
        sprite.move(0,-speed*time); //отталкивание персонажа от прямоугольника вверх
   }

//===================================================================
//------взаимодействие с исч.кругом
   if (spriteBounds.intersects(circle1Bounds))
   circle1.setFillColor(sf::Color::Black); // исчезновение при приближении персонажа

//===================================================================
//------взаимодействие с двиг. кругом
    if (spriteBounds.intersects(circle2Bounds))
    {
 //   std:: cout << "collision"<< std::endl;//(эта строка для проверки)
       if (HeroDirection==0)
        circle2.move(-speed*time,0); // отталкивание фигуры от персонажа влево
       if (HeroDirection==2)
        circle2.move(speed*time,0);// отталкивание фигуры от персонажа вправо
        if (HeroDirection==3)
        circle2.move(0,-speed*time);// отталкивание фигуры от персонажа вверх
        if (HeroDirection==4)
        circle2.move(0,speed*time);// отталкивание фигуры от персонажа вниз
    }

//===================================================================
//------взаимодействие с квадратом
 if (spriteBounds.intersects(circleBounds))
    {
 //   std:: cout << "collision"<< std::endl;//(эта строка для проверки)
 if (HeroDirection==0)
        sprite.move(-speed*time,0);//при нажатии влево отталкивание персонажа  влево
       if (HeroDirection==2)
        sprite.move(speed*time,0);//при нажатии вправо отталкивание персонажа  вправо
        if (HeroDirection==3)
        sprite.move(0,-speed*time);//при нажатии вверх отталкивание персонажа  вверх
        if (HeroDirection==4)
        sprite.move(0,speed*time);//при нажатии вниз отталкивание персонажа  вниз
    }

//===================================================================
//------собыие телепорт персонажа
 if (spriteBounds.intersects(Teleportation))
    sprite.setPosition(sf::Vector2f(200,100)); //при приближении персонажа телепортирование его в заданную точку

//===================================================================
//-------событие кнопки 1
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //нажатие на кнопку влево
{
    HeroDirection = 0;
    CurrentFrame += 0.005*time; //счетчик
    std::cout << CurrentFrame << std::endl;//вывод для консоли
    if(CurrentFrame>4) CurrentFrame -= 4;//для движения персонажа
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,96,64,96)); //вырез из картинуи
    sprite.move(-speed*time,0);//просоединение движ к времени
}
//-------событие кнопки 2
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //нажатие на кнопку вправо
{
    HeroDirection = 2;
    CurrentFrame += 0.005*time;//счетчик
    std::cout << CurrentFrame << std::endl;//вывод для консоли
    if(CurrentFrame>4) CurrentFrame -= 4;//для движения персонажа
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,192,64,96));//вырез из картинуи
    sprite.move(speed*time,0);//просоединение движ к времени
}
//-------событие кнопки 3
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //нажатие на кнопку вверх
{
    HeroDirection = 3;
    CurrentFrame += 0.005*time;//счетчик
    std::cout << CurrentFrame << std::endl;//вывод для консоли
    if(CurrentFrame>4) CurrentFrame -= 4;//для движения персонажа
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,288,64,96));//вырез из картинуи
    sprite.move(0,-speed*time);//просоединение движ к времени
}
//-------событие кнопки 4
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //нажатие на кнопку вниз
{
    HeroDirection = 4;
    CurrentFrame += 0.005*time;//счетчик
    std::cout << CurrentFrame << std::endl;//вывод для консоли
    if(CurrentFrame>4) CurrentFrame -= 4;//для движения персонажа
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,0,64,96));//вырез из картинуи
    sprite.move(0,speed*time);//просоединение движ к времени
}

//===================================================================
//-----рисование фигур:
   window.clear(sf::Color::Black);//заливка фона
   window.draw(circle);//заливка квадрата
   window.draw(circle1);//заливка круга
   window.draw(circle2);//заливка круга
   window.draw(rectangle);//заливка прямоугольника
   window.draw(rectangleTele);//заливка телепорт фигуры
   window.draw(rectangleTele2);//заливка 2-й теле. фигуры
   window.draw(sprite);//вывод картинки
   window.display(); //дисплей
    }
    return 0;
}
//200!
