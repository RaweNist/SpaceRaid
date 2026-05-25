#include "Player.h"
#include "Projectile.h"
#include "PlayerController.h"
#include "textures.h"

Player::Player(sf::Texture& texture, sf::Vector2f startpos, float health, float speed, short curlvl, TileMap* maps, short _lvls)
{
    _isAlive = true;
    c_type = 'p';
    c_pos = startpos;
    curLvl = curlvl;
    lvls = _lvls;
    c_health = health;
    c_rotation = 0;
    c_speed = speed;
    c_cooldown = 800;
    c_atcrange = 2048;
    canShoot = true;
    p_controller = PlayerController::getPlayerController();
    Maps = maps;
    
    c_sprite.setTexture(texture);
    c_sprite.setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
    c_size = sf::Vector2f(c_sprite.getTextureRect().width, c_sprite.getTextureRect().height);
    Weapon wpn("Pistol", sf::Vector2f(0, 0), 10, 15, 800, 20);
    Weapon wpn1("Assault Rifle", sf::Vector2f(0, 0), 5, 20, 200, 30);
    addWeapon(wpn);
    addWeapon(wpn1);
    cur_wpn = 0;
}

Player::~Player() {}

void Player::Update(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time) {
    c_state = State::IDLE;
    if (isAlive()) {
        textures::setTextures();
        p_controller->controllPlayer(window, this, time);
        checkCollision(map, time);
        Attack(window, map, chars, time);
        c_sprite.setPosition(c_pos);
        c_sprite.setRotation(c_rotation);        
        window.draw(getSprite());
    }
    if (_isAlive && getHP() <= 0)
        _isAlive = 0;
    
}

void Player::drawCrosshair(sf::RenderWindow& window, sf::View& view)
{
    sf::Sprite ch;
    ch.setTexture(textures::crosshair_texture);
    ch.setScale(sf::Vector2f(0.8, 0.8));
    sf::Vector2i cp = sf::Mouse::getPosition(window);
    cp.x = cp.x + (view).getCenter().x - WINDOW_WIDTH / 2;
    cp.y = cp.y + (view).getCenter().y - WINDOW_HEIGHT / 2;
    ch.setPosition(cp.x - 26, cp.y - 26);

    calcAngle(cp.x, cp.y);

    window.draw(ch);
}

int Player::checkCollision(std::string* map, float time)
{
	int h = TILE_SIZE;
	int w = TILE_SIZE;
	int dx = (int) getDirectionX();
	int dy = (int) getDirectionY();
	int i = c_pos.y / 64;
	int j = c_pos.x / 64;
	if (dy > 0 && (map[(int)(c_pos.y + 32) / 64][j] == '2' || map[(int)(c_pos.y + 32) / 64][j] == '4' /* ||
		map[(int)(c_pos.y + 16) / 64][(int)(c_pos.x + 16) / 64] == '2' || map[(int)(c_pos.y + 16) / 64][(int)(c_pos.x + 16) / 64] == '4' ||
		map[(int)(c_pos.y + 16) / 64][(int)(c_pos.x - 16) / 64] == '2' || map[(int)(c_pos.y + 16) / 64][(int)(c_pos.x - 16) / 64] == '4'*/))
	{
		if (dx == 0)
			c_pos.y -= c_speed * time;
		else
			c_pos.y -= sqrt(0.5) * c_speed * time;
	}
	else if (dy < 0 && (map[(int)(c_pos.y - 32) / 64][j] == '2' || map[(int)(c_pos.y - 32) / 64][j] == '4' /* ||
		map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x + 32) / 64] == '2' || map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x + 32) / 64] == '4' ||
		map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x - 32) / 64] == '2' || map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x - 32) / 64] == '4'*/))
	{
		if (dx == 0)
			c_pos.y += c_speed * time;
		else
			c_pos.y += sqrt(0.5) * c_speed * time;
	}
	if (dx > 0 && (map[i][(int)(c_pos.x + 32) / 64] == '2' || map[i][(int)(c_pos.x + 32) / 64] == '4' /* ||
		map[(int)(c_pos.y + 32) / 64][(int)(c_pos.x + 32) / 64] == '2' || map[(int)(c_pos.y + 32) / 64][(int)(c_pos.x + 32) / 64] == '4' ||
		map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x + 32) / 64] == '2' || map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x + 32) / 64] == '4'*/))
	{
		if (dy == 0)
			c_pos.x -= c_speed * time;
		else
			c_pos.x -= sqrt(0.5) * c_speed * time;
	}
	else if (dx < 0 && (map[i][(int)(c_pos.x - 32) / 64] == '2' || map[i][(int)(c_pos.x - 32) / 64] == '4' /*||
		map[(int)(c_pos.y + 32) / 64][(int)(c_pos.x - 32) / 64] == '2' || map[(int)(c_pos.y + 32) / 64][(int)(c_pos.x - 32) / 64] == '4' ||
		map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x - 32) / 64] == '2' || map[(int)(c_pos.y - 32) / 64][(int)(c_pos.x - 32) / 64] == '2'*/))
	{
		if (dy == 0)
			c_pos.x += c_speed * time;
		else
			c_pos.x += sqrt(0.5) * c_speed * time;
	}

    if (map[i][j] == '3') {
        map[i][j] = '1';
        c_health += 25;
    }
    else if (map[i][j] == 'A') {
        map[i][j] = '1';
        weapons[cur_wpn].setAmmo(weapons[cur_wpn].getAmmo() + 15);
    }
    else if (map[i][j] == 'E') {
        if (curLvl < lvls - 1) {
            curLvl++;
            sf::Vector2f startpos = Maps[curLvl].getPlayerPos();
            setPosition(startpos);
        }
        else {
            setState(State::WIN);
        }
    }
	return 0;
}

void Player::Attack(sf::RenderWindow& window, std::string* map, std::vector <Character*>& chars, float time)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getCanShoot() && weapons[cur_wpn].getAmmo() > 0) {
        setCanShoot(false);
        weapons[cur_wpn].setAmmo(weapons[cur_wpn].getAmmo() - 1);
        if (getTimer().getActive() == 0) {
            getTimer().start(weapons[cur_wpn].getCooldown(), [=]() { setCanShoot(true); });
        }
        Projectile pr = weapons[cur_wpn].getProjectile();
        addBullet(Projectile('P',c_pos, pr.getDamage(), pr.getSpeed(), textures::bullet_texture));
        addBulletAngle((getRotation() - 90) / 180 * PI);
    }
    checkProjectiles(window, chars, map, time);
}

void Player::UpdateHUD(sf::RenderWindow& window, sf::View& view, float time)
{
    sf::Font font;
    font.loadFromFile("PixelDigivolve-mOm9.ttf");
    if (isAlive()) {
        
        
        sf::Text hp_bar("Hp: 100 | 100", font, 40);
        sf::Text ammo_bar("Ammo : 0", font, 40);
        sf::Text weapon_bar("<-Q E->\n", font, 40);
        hp_bar.setFillColor(sf::Color::Red);
        hp_bar.setStyle(sf::Text::Regular);
        hp_bar.setPosition(view.getCenter().x + 400, view.getCenter().y + 300);
        hp_bar.setString("Hp: " + std::to_string(getHP()) + " | 100");

        ammo_bar.setFillColor(WHITE);
        ammo_bar.setStyle(sf::Text::Regular);
        ammo_bar.setPosition(view.getCenter().x + 400, view.getCenter().y + 350);
        ammo_bar.setString(getCurWeapon().getName() + "\n" + "Ammo : " + std::to_string(getCurWeapon().getAmmo()));

        weapon_bar.setFillColor(WHITE);
        weapon_bar.setStyle(sf::Text::Regular);
        weapon_bar.setPosition(view.getCenter().x + 400, view.getCenter().y - 450);
        std::string wpns = "<-Q E->\n";
        for (int i = 0; i < getWeaponsCount(); ++i)
            wpns += std::to_string(i + 1) + "-" + getWeapon(i).getName() + "\n";
        weapon_bar.setString(wpns);

        window.draw(hp_bar);
        window.draw(ammo_bar);
        window.draw(weapon_bar);
    }
    else if (!isAlive()){
        sf::Text death_screen("You Died!", font, 40);
        death_screen.setFillColor(sf::Color::Red);
        death_screen.setStyle(sf::Text::Regular);
        death_screen.setPosition(view.getCenter().x - 100, view.getCenter().y - 20);
        death_screen.setString("You Died!");
        window.draw(death_screen);
    }
    if (c_type == 'W') {
        sf::Text win_screen("You Win!", font, 100);
        win_screen.setFillColor(sf::Color::Red);
        win_screen.setStyle(sf::Text::Regular);
        win_screen.setPosition(view.getCenter().x - 220, view.getCenter().y - 60);
        win_screen.setString("You Win!");
        window.draw(win_screen);
    }
    view.setCenter(getPosition());
    drawCrosshair(window, view);
}

int Player::getCurLvl() const
{
    return curLvl;
}

State Player::getState() const
{
    return c_state;
}

void Player::addWeapon(Weapon& wpn)
{
    weapons.push_back(wpn);
}

Weapon& Player::getWeapon(unsigned i)
{
    return weapons[i];
}

Weapon& Player::getCurWeapon()
{
    return weapons[cur_wpn];
}

int Player::getCurWeaponId()
{
    return cur_wpn;
}

int Player::getWeaponsCount()
{
    return weapons.size();
}

void Player::prewWeapon()
{
    if (cur_wpn != 0)
        cur_wpn--;
    else cur_wpn = weapons.size() - 1;
}

void Player::nextWeapon()
{
    if (cur_wpn + 1 != weapons.size())
        cur_wpn++;
    else cur_wpn = 0;
}

void Player::setState(State state) {
    c_state = state;
}
