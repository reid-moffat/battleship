/**
 * File: button.h
 * Description: Front-end class that creates buttons and manages button states, textures, and sprites
 */

#ifndef BATTLESHIP_BUTTON_H
#define BATTLESHIP_BUTTON_H

#include <SFML/Graphics.hpp>

namespace entity {

    class Button {
    private:
        /**
         * Idle button texture
         */
        sf::Texture idleTexture;

        /**
         * Active button texture
         */
        sf::Texture activeTexture;

        /**
         * Button sprite
         */
        sf::Sprite sprite;

        /**
         * Button state (Active = true and Idle = false)
         */
        bool buttonState;

    public:
        /**
         * Constructor
         */
        Button(sf::Vector2f position, sf::Vector2f scale, sf::Texture idleTexture, sf::Texture activeTexture);

        /**
         * Copy Constructor
         */
        Button(const Button &source);

        /**
         * Destructor:
         */
        ~Button();

        /**
         * Overloaded assignment operator
         */
        Button &operator=(const Button &source);

        /**
         * Returns true if the button is active (i.e., the cursor is over the button)
         */
        const bool getButtonState() const;

        /**
         * Renders the button sprite on the window
         */
        void render(sf::RenderWindow &window) const;

        /**
         * Updates the button state and sets the button sprite to idleTexture or activeTexture depending on the current state
         */
        void updateButtonState(const sf::Vector2f mousePosition);
    };

}// namespace entity

#endif// BATTLESHIP_BUTTON_H