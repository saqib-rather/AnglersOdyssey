void Menu::update(sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (menuItems[i].getGlobalBounds().contains(mousePos)) {
            menuItems[i].setFillColor(sf::Color::Yellow);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                selectedItem = i;
            }
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}
