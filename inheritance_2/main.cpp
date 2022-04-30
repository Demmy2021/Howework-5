#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
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
        move(x_speed_*dt,y_speed_*dt);
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
      bool isClicked(sf::Vector2i &mouse_position)
      {
          sf::FloatRect rectangle_bounds = getGlobalBounds();
          if(mouse_position.x >= rectangle_bounds.left &&
             mouse_position.x <= rectangle_bounds.left + rectangle_bounds.width
             && mouse_position.y >= rectangle_bounds.top &&
             mouse_position.y <= rectangle_bounds.top + rectangle_bounds.height)
          {
              return true;
          }
          return false;
      }

      bool isColorActive(){return active_;}
         void makeActive(){
             setFillColor(sf::Color(255,0,0));
             active_ = true;
         }
         void dactivateColor(){
             setFillColor(sf::Color(0,255,0));
             active_ = false;
         }


private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    float active_ = 0;


    void bounce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }


};


void create_shapes(std::vector<std::unique_ptr<sf::Drawable>> &shapes_vec) {
    sf::Vector2f size(120.0, 60.0);
        auto rec = std::make_unique<sf::RectangleShape>(size);
        rec -> setPosition(50.0, 400.0);
     auto cir = std::make_unique<sf::CircleShape>(60.0);

     shapes_vec.emplace_back(std::move(rec));
     shapes_vec.emplace_back(std::move(cir));
}



int main() {


    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::vector<std::unique_ptr<sf::Drawable>> shape_vector;

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

    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);

    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle(size, position);
    rectangle.setFillColor(sf::Color(150, 100, 50));
    rectangle.setSpeed(100, 150, 10);

    //sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::Clock clock;

    int rectangle_velocity_x = 20;
    int rectangle_velocity_y = 30;


    bool flag_y = false;
    bool flag_x = false;
    rectangle.setTexture(&texture_guy);

    // run the program as long as the window is open
    while (window.isOpen()) {


        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);

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


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
              if(event.type == sf::Event::MouseButtonPressed)
                    {
                  if(event.mouseButton.button == sf::Mouse::Left)
                    std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                      rectangle.animate(elapsed);
                      rectangle.dactivateColor();
                    if(rectangle.isClicked(mouse_pos))
                    rectangle.makeActive();
                    std::cout << "Space released" << std::endl;
                }

  sf::Keyboard::Key pressed;
  if(event.type == sf::Event::KeyPressed)
           {
            pressed = event.key.code;
            rectangle.animate(elapsed);
           if(rectangle.isColorActive())
            rectangle.moveInDirection(elapsed,pressed);

           }


        // clear the window with black color
         window.clear(sf::Color::Black);
         window.draw(sprite);
         window.draw(wall);
         window.draw(rectangle);
        // end the current frame
        window.display();
    }

    return 0;
}
