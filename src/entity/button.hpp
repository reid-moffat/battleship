/**
 * Front-end class for a buttons that can render a texture, change textures
 * and tell if the mouse is hovering over it
 */

#ifndef BATTLESHIP_BUTTON_H
#define BATTLESHIP_BUTTON_H

#include <SFML/Graphics.hpp>

namespace entity {

    class Button {
    public:
        /**
         * Constructs a new button
         *
         * @param position the position on the screens
         * @param scale a vector to scale the button by (e.g (2, 2) to double its width and height)
         * @param idleTexture the texture of this button when the mouse is not hovering over it
         * @param activeTexture the texture of this button when the mouse is hovering over it
         */
        Button(sf::Vector2f position, sf::Vector2f scale, sf::Texture &idleTexture, sf::Texture &activeTexture);

        /**
         * Returns true if the button is active (i.e., the cursor is over the button)
         */
        [[nodiscard]] bool getButtonState() const;

        /**
         * Renders the button sprite on the window
         */
        void render(sf::RenderWindow &window) const;

        /**
         * Updates the button state and texture if the mouse is over the button
         */
        void updateButtonState(sf::Vector2f mousePosition);

        // Big three
        Button(const Button &source);
        ~Button();
        Button &operator=(const Button &source);

    private:
        /**
         * Texture when the button does not have the mouse over it
         */
        sf::Texture *idleTexture;

        /**
         * Texture when the button has the mouse over it
         */
        sf::Texture *activeTexture;

        /**
         * Button sprite (the object that renders)
         */
        sf::Sprite *sprite;

        /**
         * Button state (true and Idle = false)
         */
        bool active;
    };

}// namespace entity

#endif// BATTLESHIP_BUTTON_H