#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
    {
        setPosition(position);
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void animate(const sf::Time &elapsed){
        bounce();
        float dt = elapsed.asSeconds();
        move(x_speed_*dt, y_speed_*dt);
        //rotate(ro_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

       void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
      {
          float dt = elapsed.asSeconds();
            if(key == sf::Keyboard::Up)
          {
              y_speed_ = -1*abs(y_speed_);
                          bounce();

         move(0, y_speed_ * dt);
          }
          else if(key == sf::Keyboard::Down)
          {
              y_speed_ = abs(y_speed_);
                          bounce();
                  move(0, y_speed_ * dt);
                   }
          else if(key == sf::Keyboard::Left)
          {
              x_speed_ = -1*abs(x_speed_);
                          bounce();

              move(x_speed_ * dt, 0);
              }
          else if(key == sf::Keyboard::Right)
          {
              x_speed_ = abs(x_speed_);
                         bounce();

                   move(x_speed_ * dt, 0);
          }
      }

private:

    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;




    void bounce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            //setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
           //setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            //setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }



};


//void create_shapes(std::vector<std::unique_ptr<sf::Drawable>> &shapes_vec) {
//    sf::Vector2f size(120.0, 60.0);
//        auto rec = std::make_unique<sf::RectangleShape>(size);
//        rec -> setPosition(50.0, 400.0);
//     //auto cir = std::make_unique<sf::CircleShape>(60.0);

//     shapes_vec.emplace_back(std::move(rec));
//     //shapes_vec.emplace_back(std::move(cir));
//}



int main() {


    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::vector<std::unique_ptr<sf::Drawable>> shape_vector;



    std::srand(std::time(nullptr));

    sf::Texture texture;
    if (!texture.loadFromFile("grass.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
    texture.setRepeated(true);

    sf::Texture texture_guy;
    if(!texture_guy.loadFromFile("guy.png")) {
        return 1; }

    sf::Sprite guy;
    guy.setTexture(texture_guy);
    guy.setTextureRect(sf::IntRect(10, 20, 20, 15)); //left, top, width, height
    texture_guy.setRepeated(true);

    //sf::Transformable::setScale;
    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("wall.png")) {
        return 1; }
std::vector<sf::Texture> walls;

    sf::Sprite wall_1;
    wall_1.setTexture(texture_wall);
    wall_1.setScale(0.6, 0.6);
    wall_1.setPosition(sf::Vector2f(150, 150)); // absolute position
    wall_1.move(sf::Vector2f(20, 20));
    wall_1.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);

    sf::Sprite wall_2;
    wall_2.setTexture(texture_wall);
    wall_2.setScale(0.6, 0.6);
    wall_2.setPosition(sf::Vector2f(10, 50)); // absolute position
    wall_2.move(sf::Vector2f(20, 20));
    wall_2.setTextureRect(sf::IntRect(0, 0, 60, 350));
    texture_wall.setRepeated(true);

    sf::Sprite wall_3;
    wall_3.setTexture(texture_wall);
    wall_3.setScale(0.6, 0.6);
    wall_3.setPosition(sf::Vector2f(450, 120)); // absolute position
    wall_3.move(sf::Vector2f(20, 20));
    wall_3.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);

    sf::Sprite wall_4;
    wall_4.setTexture(texture_wall);
    wall_4.setScale(0.6, 0.6);
    wall_4.setPosition(sf::Vector2f(225, 120)); // absolute position
    wall_4.move(sf::Vector2f(20, 20));
    wall_4.setRotation(-90); // absolute angle
    wall_4.setTextureRect(sf::IntRect(0, 0, 60, 250));
    texture_wall.setRepeated(true);

    sf::Sprite wall_5;
    wall_5.setTexture(texture_wall);
    wall_5.setScale(0.6, 0.6);
    wall_5.setPosition(sf::Vector2f(450, 350)); // absolute position
    wall_5.move(sf::Vector2f(20, 20));
    wall_5.setRotation(-90); // absolute angle
    wall_5.setTextureRect(sf::IntRect(0, 0, 60, 250));
    texture_wall.setRepeated(true);

       sf::Vector2f size(40.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle(size, position);
    rectangle.setFillColor(sf::Color(150, 100, 50));

    rectangle.setSpeed(100, 150, 10);

    sf::Clock clock;

    int rectangle_velocity_x = 20;
    int rectangle_velocity_y = 30;


    bool flag_y = false;
    bool flag_x = false;

   rectangle.setTexture(&texture_guy);

    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();
        //float dt = elapsed.asSeconds();

        //rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);

        rectangle.setBounds(0, window.getSize().x, 0, window.getSize().y);

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        if(rectangle_bounds.top<=0 || rectangle_bounds.top+rectangle_bounds.height>=window.getSize().y)
            {
                if(flag_y != true)
                {
                    rectangle_velocity_y *= -1;
         }
                flag_y = true;
            }
            else
                flag_y = false;

            if(rectangle_bounds.left<=0 || rectangle_bounds.left+rectangle_bounds.width>=window.getSize().x)
            {
                if(flag_x!=true)
                {
                    rectangle_velocity_x *= -1;
                  }
                flag_x = true;
            }
            else
                flag_x = false;

           sf::Event event;
        while (window.pollEvent(event)) {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        mouse_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
        sf::Keyboard::Key pressed;
          if(event.type == sf::Event::KeyPressed)
                   {
                   pressed = event.key.code;
                   rectangle.moveInDirection(elapsed,pressed);
                   //rectangle.moveInDirection2(elapsed,pressed);
                   rectangle.animate(elapsed);
                       }
       // clear the window with black color
         window.clear(sf::Color::Black);
         window.draw(sprite);
         window.draw(wall_1);
         window.draw(wall_2);
         window.draw(wall_3);
         window.draw(wall_4);
         window.draw(wall_5);
         //WindowBoundsCollision(wall_1, wall_2, wall_3,wall_4,wall_5);
         window.draw(rectangle);
         // end the current frame
        window.display();
    }

    return 0;
}