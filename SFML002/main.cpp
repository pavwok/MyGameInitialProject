#include <SFML/Graphics.hpp> //��� ���������� sfml �������
#include <cstdlib> //��� ���������� ��� ��� std
#include <windows.h> // ��� ���������� ��� ������ � windows
#include <iostream> //��� ����������� ����������


using namespace sf; // ( ��� ��� ������������:] )

 sf::RenderWindow window; //������ ����
 sf::CircleShape circle(50,4); //������ �������
 sf::RectangleShape rectangle(sf::Vector2f(150,70)); // ������� �������������
 sf::RectangleShape rectangleTele(sf::Vector2f(10,70));//��������������� ������
 sf::RectangleShape rectangleTele2(sf::Vector2f(10,70));//2-� ������ ��� ���������
 sf::CircleShape circle1(25,10); //���������� ����
 sf::CircleShape circle2(20,30); // ����������� ����
 sf::Image image; //��� ��������
 sf::Texture texture; //���������
 sf::Sprite sprite;

 float speed = 0.1; //�������� ���������
 float CurrentFrame = 0;
 int HeroDirection; //��������


int main()
{
//�������� ������
    window.create(sf::VideoMode(640,480),"Walking man");
window.setFramerateLimit(60);//���-�� ����/���


//===================================================================
    circle.setFillColor(sf::Color::Yellow); //���� ��������
    circle.setPosition(200,350); //������ ��������
    circle.rotate(45); // ������� ������ ( ���� ������, �� ����� ����)

    rectangle.setFillColor(sf::Color::Cyan); // ���� �����. ��������������
    rectangle.setPosition(200,200); //������ ��������������

    circle1.setFillColor(sf::Color::Yellow); //���� ���.�����
    circle1.setPosition(300,400); //������ �����

    circle2.setFillColor(sf::Color::Red); //���� ����. �����
    circle2.setPosition(500,200); //������ �����

//===================================================================
    image.loadFromFile("image.png");//���� � �������� � ����������
    texture.loadFromImage(image);//�������������� � ��������
    sprite.setTexture(texture);//������ �������� � �������������
    sprite.setPosition(50,50);  // ������ ��������
   sprite.setTextureRect(sf::IntRect(0,0,64,96)); //����� �� ��������

//===================================================================
     rectangleTele.setFillColor(sf::Color::Green); //��������������� ������
    rectangleTele.setPosition(100,100); // ������

  rectangleTele2.setFillColor(sf::Color::Green); // 2-� ������ ��� ���������
    rectangleTele2.setPosition(200,100); // ������

//===================================================================
    sf::Clock clock; // ���������� ���������� �������

    while (window.isOpen()) // ���� ������� ����
    {
//�������� �����:
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

//===================================================================
//-------������� ��� ����:
   sf::Event event;//�������� ��������� ����
   while (window.pollEvent(event))
   {
//���� ������ �� ������ �������:
       if (event.type == sf::Event::Closed)
        window.close();
   }

//===================================================================
//----������� �������������� ��������� � ���������
   sf::FloatRect spriteBounds = sprite.getGlobalBounds();// ������� ������ ���������
   sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();// ������� ������ ��������������
sf::FloatRect circle1Bounds = circle1.getGlobalBounds();// ������� ������ ���.�����
sf::FloatRect circle2Bounds = circle2.getGlobalBounds();// ������� ������ ����. �����
sf::FloatRect circleBounds = circle.getGlobalBounds();//������� ������ ��������
sf::FloatRect Teleportation = rectangleTele.getGlobalBounds();//������� ������ ���������

//===================================================================
//------�������������� � ���������������
   if (spriteBounds.intersects(rectangleBounds))
    {
   // std:: cout << "collision"<< std::endl; //(��� ������ ��� ��������)
       if (HeroDirection==0)
        sprite.move(speed*time,0); //������������ ��������� �� �������������� ������
       if (HeroDirection==2)
        sprite.move(-speed*time,0);//������������ ��������� �� �������������� �����
        if (HeroDirection==3)
        sprite.move(0,speed*time);//������������ ��������� �� �������������� ����
        if (HeroDirection==4)
        sprite.move(0,-speed*time); //������������ ��������� �� �������������� �����
   }

//===================================================================
//------�������������� � ���.������
   if (spriteBounds.intersects(circle1Bounds))
   circle1.setFillColor(sf::Color::Black); // ������������ ��� ����������� ���������

//===================================================================
//------�������������� � ����. ������
    if (spriteBounds.intersects(circle2Bounds))
    {
 //   std:: cout << "collision"<< std::endl;//(��� ������ ��� ��������)
       if (HeroDirection==0)
        circle2.move(-speed*time,0); // ������������ ������ �� ��������� �����
       if (HeroDirection==2)
        circle2.move(speed*time,0);// ������������ ������ �� ��������� ������
        if (HeroDirection==3)
        circle2.move(0,-speed*time);// ������������ ������ �� ��������� �����
        if (HeroDirection==4)
        circle2.move(0,speed*time);// ������������ ������ �� ��������� ����
    }

//===================================================================
//------�������������� � ���������
 if (spriteBounds.intersects(circleBounds))
    {
 //   std:: cout << "collision"<< std::endl;//(��� ������ ��� ��������)
 if (HeroDirection==0)
        sprite.move(-speed*time,0);//��� ������� ����� ������������ ���������  �����
       if (HeroDirection==2)
        sprite.move(speed*time,0);//��� ������� ������ ������������ ���������  ������
        if (HeroDirection==3)
        sprite.move(0,-speed*time);//��� ������� ����� ������������ ���������  �����
        if (HeroDirection==4)
        sprite.move(0,speed*time);//��� ������� ���� ������������ ���������  ����
    }

//===================================================================
//------������ �������� ���������
 if (spriteBounds.intersects(Teleportation))
    sprite.setPosition(sf::Vector2f(200,100)); //��� ����������� ��������� ���������������� ��� � �������� �����

//===================================================================
//-------������� ������ 1
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //������� �� ������ �����
{
    HeroDirection = 0;
    CurrentFrame += 0.005*time; //�������
    std::cout << CurrentFrame << std::endl;//����� ��� �������
    if(CurrentFrame>4) CurrentFrame -= 4;//��� �������� ���������
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,96,64,96)); //����� �� ��������
    sprite.move(-speed*time,0);//������������� ���� � �������
}
//-------������� ������ 2
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //������� �� ������ ������
{
    HeroDirection = 2;
    CurrentFrame += 0.005*time;//�������
    std::cout << CurrentFrame << std::endl;//����� ��� �������
    if(CurrentFrame>4) CurrentFrame -= 4;//��� �������� ���������
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,192,64,96));//����� �� ��������
    sprite.move(speed*time,0);//������������� ���� � �������
}
//-------������� ������ 3
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //������� �� ������ �����
{
    HeroDirection = 3;
    CurrentFrame += 0.005*time;//�������
    std::cout << CurrentFrame << std::endl;//����� ��� �������
    if(CurrentFrame>4) CurrentFrame -= 4;//��� �������� ���������
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,288,64,96));//����� �� ��������
    sprite.move(0,-speed*time);//������������� ���� � �������
}
//-------������� ������ 4
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //������� �� ������ ����
{
    HeroDirection = 4;
    CurrentFrame += 0.005*time;//�������
    std::cout << CurrentFrame << std::endl;//����� ��� �������
    if(CurrentFrame>4) CurrentFrame -= 4;//��� �������� ���������
    sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64,0,64,96));//����� �� ��������
    sprite.move(0,speed*time);//������������� ���� � �������
}

//===================================================================
//-----��������� �����:
   window.clear(sf::Color::Black);//������� ����
   window.draw(circle);//������� ��������
   window.draw(circle1);//������� �����
   window.draw(circle2);//������� �����
   window.draw(rectangle);//������� ��������������
   window.draw(rectangleTele);//������� �������� ������
   window.draw(rectangleTele2);//������� 2-� ����. ������
   window.draw(sprite);//����� ��������
   window.display(); //�������
    }
    return 0;
}
//200!
