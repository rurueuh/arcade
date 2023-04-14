/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-lucas.mariette
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML()
{
    _window.create(sf::VideoMode(1920, 1080), "SFML");
    _window.setFramerateLimit(60);
}

SFML::~SFML()
{
    _window.close();
}

void SFML::setAsset(std::map<char, std::string> asset)
{
    _asset = asset;
    loadAsset();
}

void SFML::loadAsset()
{
    for (auto &i : _asset) {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        sf::Sprite sprite;
        if (!texture->loadFromFile(i.second))
            throw std::runtime_error("Error while loading texture");
        sprite.setTexture(*texture);
        _mapSprite[i.first] = std::make_pair(sprite, texture);
    }
}

void SFML::setMap(std::vector<std::string> map)
{
    _map = map;
}

void SFML::draw()
{
    _window.clear();
    for (int x = 0; x < _map.size(); x++) {
        for (int y = 0; y < _map[x].size(); y++) {
            _mapSprite[_map[x][y]].first.setPosition(y * 32, x * 32);
            _window.draw(_mapSprite[_map[x][y]].first);
        }
    }
    _window.display();
}

std::string SFML::getEvent()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape)
                _window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                std::cout << "Honouring his family name was never enough for Kazan Yamaoka. He wanted to surpass his father's reputation and end what he saw as the thinning of samurai culture with farmers often posing as samurai. His father tried to turn Kazan's attention to more noble pursuits, but Kazan refused to heed his advice, and borrowing his father's Katana, he embarked on a dark pilgrimage to prove his worth and rid Japan of impostors. Ignoring the code that had been taught to him, Kazan killed impostors in the hills and the valleys, on the beaches and in the woodland. The killings were brutal, cruel and morbid. He humiliated farmers and warriors alike, yanking off their topknots and stripping them of their armour. His rage, bloodlust and perverse sense of honour knew no bounds. Monks believed he was possessed by something dark and otherworldly and cursed him while a noble lord began to call him 'Oni-Yamaoka,' the rageful Samurai, an insult both to Kazan and his family. Determined to redeem his family's name, Kazan now butchered anyone who dared call him Oni-Yamaoka. The insult confused him. He had defeated the best and he had purified the samurai class by ridding the land of impostors. How could anyone refer to him as an ogre? Had it been because he had marched onto a battlefield to cut down the fiercest warriors. Had it been because he had taken a Kanabo and dashed hundreds of skulls with it? Or had it been because of his need to secure a 'trophy' from his victims. It didn't matter. Being called an ogre was more than he could bear and an ominous voice in his head urged him to strike down the lord who had desecrated his name. As Kazan made for the lord's town, he suddenly found himself face to face with a samurai standing on a dirt road, blocking his way. Kazan readied his Kanabo. Without a word, the samurai attacked and quickly secured the upper hand. But he hesitated. With a devastating blow, Kazan crushed the samurai's head and cracked his helmet. As Kazan approached the fallen samurai, he saw his father's face and staggered back to his haunches. His father stared at Kazan with mingled shame and regret as he issued his last breath. Kazan closed his eyes and screamed in agony until he could scream no more. When he opened his eyes again... his father was gone. Not only had he killed his father, but he had allowed thieves to steal his body for armour. Bitter, lost and disillusioned, Kazan roamed the land aimlessly with his father's voice rattling in his head, taunting him, reminding him of his failures, sending him into fits of uncontrollable black rage. One day, walking in the woods, Kazan happened upon an Oni statue. He stopped and stood motionless for a long moment. The weathered and overgrown statue seemed to be ridiculing him, accusing him of being the impostor samurai he had so desperately sought to destroy. Kazan shook the laughing voice out of his head and half remembered the lord who had ridiculed him as 'Oni-Yamaoka.' With renewed anger, Kazan journeyed to a town high up in the snowy mountains where the lord resided. A dozen samurai met Kazan at the gates of the town. A dozen samurai fell to his Kanabo. His speed and strength were unmatched. His rage was incomprehensible. Covered in blood and gore, Kazan battled through the town and soon found the lord hiding in a villa. He dragged him out of a cabinet, sliced his tendons to immobilise him and watched him beg and squirm like a dog. Without hesitation, he thrust his fist into the lord’s mouth and yanked out the wicked tongue that had desecrated his name. Satisfied, Kazan exited the villa to find himself surrounded by dozens of farmers wielding rusted scythes, sharp pitchforks, and heavy clubs. He survived the first few assaults, but there were too many attackers coming from every direction. Within moments Kazan was on the ground staring at a cold, indifferent, darkening sky as farmers took turns stabbing and torturing the 'Oni' who had butchered their beloved lord. The frenzied mob dragged Kazan into a small stone mill to continue the torture and finally left him to die a slow, agonising death. When they returned, the mill was filled with a strange black fog and Kazan’s body and the Kanabo were nowhere to be found. It was the beginning of a dark legend about a rageful Oni haunting the town." << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return "Z";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return "S";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return "Q";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return "D";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return " ";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        return "L";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return "M";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return "P";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        return "I";
    return "";
}

void SFML::drawMenu(std::vector<std::pair<std::string, bool>> &menuGraphic, std::vector<std::pair<std::string, bool>> &menuGames)
{
    _window.clear();

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("./assets/background.jpg")) {
        throw std::runtime_error("Error while loading background image");
    }
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setPosition(0, 0);

    bgSprite.setScale(1920.0f / bgTexture.getSize().x, 1080.0f / bgTexture.getSize().y);
    _window.draw(bgSprite);
    drawHighscore();

    for (int i = 0; i < menuGraphic.size(); i++) {
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("./assets/font.ttf"))
            throw std::runtime_error("Error while loading font");
        text.setFont(font);
        text.setString(menuGraphic[i].first);
        text.setCharacterSize(24);
        if (menuGraphic[i].second) {
            text.setFillColor(sf::Color::Red);
            text.setCharacterSize(30);
        }
        text.setPosition(100, 100 + (i * 50));
        _window.draw(text);
    }
    for (int i = 0; i < menuGames.size(); i++) {
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("./assets/font.ttf"))
            throw std::runtime_error("Error while loading font");
        text.setFont(font);
        text.setString(menuGames[i].first);
        text.setCharacterSize(24);
        if (menuGames[i].second) {
            text.setFillColor(sf::Color::Red);
            text.setCharacterSize(30);
        }
        text.setPosition(1000, 100 + (i * 50));
        _window.draw(text);
    }
    _window.display();
}

void SFML::drawHighscore()
{
        std::ifstream file("score.txt");

    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier score.txt" << std::endl;
        return;
    }

    std::vector<std::string> scores;
    std::string line;
    while (std::getline(file, line)) {
        scores.push_back(line);
    }

    file.close();
    std::sort(scores.begin(), scores.end(), compareScore);
    sf::Font font;
    if (!font.loadFromFile("./assets/font.ttf")) {
        std::cerr << "Erreur lors du chargement de la police de caractères" << std::endl;
        return;
    }

    std::vector<sf::Text> texts;
    for (int i = 0; i < scores.size() && i < 5; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString("place n" + std::to_string(1 + i) + ": " + scores[i]);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 700 + (i * 50));
        texts.push_back(text);
    }
    for (auto &text : texts) {
        _window.draw(text);
    }
}



extern "C" std::shared_ptr<ILib> create()
{
    return std::make_shared<SFML>();
}

bool SFML::compareScore(const std::string& s1, const std::string& s2)
 {
        int score1 = getScore(s1);
        int score2 = getScore(s2);
        return score1 > score2;
}

int SFML::getScore(const std::string& s) {
    std::stringstream ss(s);
    std::string nom;
    int score;
    ss >> nom >> score;
    return score;
};