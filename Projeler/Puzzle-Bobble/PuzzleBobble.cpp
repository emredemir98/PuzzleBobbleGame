#include<SFML/Graphics.hpp>
#define M_PI 3.14159265358979323846
#include <vector>
#include<iostream>
#include< cmath >

enum RENK
{
	KIRMIZI, SARI, MAVI, YESIL,
};

int silinecekToplar[100] = { 0 };

int silinecekTopSayisi = 1;
std::vector<sf::CircleShape> toplar;
std::vector<sf::CircleShape> silinenToplar;
sf::Image image;
sf::Texture kaplama;
bool anim_yapisma = false;
bool anim_patlama = false;

void yokEdilecekleriBul(sf::CircleShape gelenTop)
{
	for (int i = 0; i < toplar.size(); i++)
	{
		sf::CircleShape top = toplar.at(i);
		if (floor(sqrt(pow(gelenTop.getPosition().y - top.getPosition().y, 2) + pow(gelenTop.getPosition().x - top.getPosition().x, 2))) <= 2 * gelenTop.getRadius())
		{
			if (top.getFillColor() == gelenTop.getFillColor())
			{
				if (silinecekToplar[i] == 0)
				{
					silinecekToplar[i] = 1;
					silinecekTopSayisi++;
				}
				if (i != toplar.size() - 1 && silinecekToplar[i] != 2)
				{
					silinecekToplar[i] = 2;
					yokEdilecekleriBul(top);
				}
			}
		}
	}
}

void dusmeyenleriBul(sf::CircleShape gelenTop) {

	for (int i = 0; i < toplar.size(); i++)
	{

		sf::CircleShape top = toplar.at(i);

		if (floor(sqrt(pow(gelenTop.getPosition().y - top.getPosition().y, 2) + pow(gelenTop.getPosition().x - top.getPosition().x, 2))) <= 2 * gelenTop.getRadius())
		{
			if (silinecekToplar[i] == 0)
			{
				silinecekToplar[i] = 3;
				dusmeyenleriBul(top);
				//silinecekTopSayisi++;
			}
		}
	}

}
void toplariSil(float ustSinir)
{

	if (silinecekTopSayisi >= 3)
	{
		for (int i = toplar.size() - 1; i >= 0; i--)
		{
			if (silinecekToplar[i] != 0)
			{
				silinenToplar.push_back(toplar.at(i));
				toplar.erase(toplar.begin() + i);
			}
		}
		anim_patlama = true;
	}
	else
	{
		anim_yapisma = true;
	}
	std::memset(silinecekToplar, 0, sizeof(silinecekToplar));
	silinecekTopSayisi = 1;

	if (toplar.size() != 0)
	{
		for (int i = 0; i < toplar.size(); i++)
		{
			if (toplar[i].getPosition().y == toplar[i].getRadius() + ustSinir)
			{
				dusmeyenleriBul(toplar.at(i));

			}
		}
		for (int i = toplar.size() - 1; i >= 0; i--)
		{
			if (silinecekToplar[i] != 3)
			{
				toplar.erase(toplar.begin() + i);
			}
		}
		std::memset(silinecekToplar, 0, sizeof(silinecekToplar));
	}
}

sf::Color renkBelirle(int renkKodu) {
	if (renkKodu == KIRMIZI)
		return sf::Color::Red;
	if (renkKodu == SARI)
		return sf::Color::Yellow;
	if (renkKodu == MAVI)
		return sf::Color::Blue;
	if (renkKodu == YESIL)
		return sf::Color::Green;
	else
		return sf::Color::Black;
}

int main()
{
	if (image.loadFromFile("../../bin/resimler/puzzle.png"))
	{
		auto maskerengi = image.getPixel(6, 1680);
		image.createMaskFromColor(maskerengi);
		kaplama.loadFromImage(image);
	}
	else
	{
		std::cout << "Dosya yüklerken hata oluþtu";
	}

	sf::Sprite toplarSprite[5][14];   /// mavi  kýrmýzý sarý yeþil gri
	sf::Sprite canavarlar[2][14];   /// canavarlar
	sf::Sprite cark[12];   /// cark
	sf::Sprite carktopu[8];   /// cark 1041 1812
	sf::Sprite ok[1];   /// 

	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 14; j++)
		{
			if (j < 8)
			{
				if (i % 2 == 0)
				{
					toplarSprite[i][j].setTexture(kaplama);
					toplarSprite[i][j].setTextureRect(sf::IntRect(sf::Vector2i(1 + (j * 17), 2614 + i * 33), sf::Vector2i(16, 16)));
				}
				else
				{
					toplarSprite[i][j].setTexture(kaplama);
					toplarSprite[i][j].setTextureRect(sf::IntRect(sf::Vector2i(436 + (j * 17), 2614 + i / 2 * 33), sf::Vector2i(16, 16)));
				}

			}
			else
			{
				//171 1846
				toplarSprite[i][j].setTexture(kaplama);
				toplarSprite[i][j].setTextureRect(sf::IntRect(sf::Vector2i(171 + (j % 8 * 33), 1846 + i * 33), sf::Vector2i(32, 32)));
			}
		}

	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (j < 8)
			{
				if (i % 2 == 0)
				{
					toplarSprite[i + 2][j].setTexture(kaplama);
					toplarSprite[i + 2][j].setTextureRect(sf::IntRect(sf::Vector2i(1 + (j * 17), 2647 + i * 33), sf::Vector2i(16, 16)));
				}
				else
				{
					toplarSprite[i + 2][j].setTexture(kaplama);
					toplarSprite[i + 2][j].setTextureRect(sf::IntRect(sf::Vector2i(436 + (j * 17), 2647 + i / 2 * 33), sf::Vector2i(16, 16)));
				}
			}

			else
			{
				toplarSprite[i + 2][j].setTexture(kaplama);
				toplarSprite[i + 2][j].setTextureRect(sf::IntRect(sf::Vector2i(725 + (j % 8 * 33), 1846 + i * 33), sf::Vector2i(32, 32)));
			}
		}
	}
	toplarSprite[4][0].setTexture(kaplama);
	toplarSprite[4][0].setTextureRect(sf::IntRect(sf::Vector2i(1, 2713), sf::Vector2i(16, 16)));
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			canavarlar[i][j].setTexture(kaplama);
			canavarlar[i][j].setTextureRect(sf::IntRect(sf::Vector2i(1 + (j * 33), 2012 + i * 33), sf::Vector2i(32, 32)));
		}
	}
	for (int i = 0; i < 12; i++)
	{
		cark[i].setTexture(kaplama);
		cark[i].setTextureRect(sf::IntRect(sf::Vector2i(1 + (i * 65), 1805), sf::Vector2i(64, 40)));
	}
	for (int i = 0; i < 8; i++)
	{
		if (i < 4) {
			carktopu[i].setTexture(kaplama);
			carktopu[i].setTextureRect(sf::IntRect(sf::Vector2i(1041 + (i * 17), 1812), sf::Vector2i(16, 16)));
		}
		else {
			carktopu[i].setTexture(kaplama);
			carktopu[i].setTextureRect(sf::IntRect(sf::Vector2i(1041 + (i % 4 * 17), 1829), sf::Vector2i(16, 16)));
		}
	}

	ok[0].setTexture(kaplama);
	ok[0].setTextureRect(sf::IntRect(sf::Vector2i(66, 1545), sf::Vector2i(64, 60)));
	ok[0].rotate(-2.0f);
	std::memset(silinecekToplar, 0, sizeof(silinecekToplar));
	srand(time(NULL));
	sf::Font font;

	if (!font.loadFromFile("Ponymaker-nzAg.ttf"))
	{
		std::cout << "Dosya yüklerken hata oluþtu";
	}

	int yaricap = 20;
	sf::RenderWindow pencere(sf::VideoMode(yaricap * 2 * 8, yaricap * 2 * 11), "Odev 1");
	float saniyedekiCerceveSayisi = 60.0f;

	sf::CircleShape ateslenecekTop(yaricap);
	sf::RectangleShape ustSinir(sf::Vector2f(pencere.getSize().x, 10));
	sf::RectangleShape altSinir(sf::Vector2f(pencere.getSize().x, 2));
	sf::RectangleShape silah(sf::Vector2f(2, yaricap * 3));
	pencere.setKeyRepeatEnabled(false);
	sf::Clock sure;
	int ilkRenkler[30]{ KIRMIZI,KIRMIZI,SARI,SARI,MAVI,MAVI,YESIL,YESIL,KIRMIZI,KIRMIZI,SARI,SARI,MAVI,MAVI,YESIL,MAVI,MAVI,YESIL,YESIL,KIRMIZI,KIRMIZI,SARI,SARI,MAVI,YESIL,YESIL,KIRMIZI,KIRMIZI,SARI,SARI };



	float  cerceveSuresi = 1.0f / saniyedekiCerceveSayisi;
	bool oyunbasliyor = true;
	float topx = pencere.getSize().x / 2;
	float topy = pencere.getSize().y - 3 * ateslenecekTop.getRadius() - 10;
	float artisx;
	float artisy;
	int satir;
	bool tepedeMi = false;
	int atilanTopSayisi = 0;
	bool oyunBittiMi = false;
	float silahAci = 0;
	bool ateslendiMi = false;
	float carkindex = 4;
	float carktopuindex = 4;
	float canavarindex = 0;
	float canavar2index = 8;
	bool carkcalisiyor = false;
	float yapismaIndex = 0;
	float patlamaIndex = 8;

	while (pencere.isOpen())
	{
		if (oyunbasliyor) {
			pencere.clear();
			toplar.clear();
			ateslenecekTop.setOrigin(sf::Vector2f(ateslenecekTop.getRadius(), ateslenecekTop.getRadius()));
			ateslenecekTop.setFillColor(renkBelirle(rand() % 4));
			ateslenecekTop.setPosition(sf::Vector2f(topx, topy));
			ustSinir.setOrigin(sf::Vector2f(0, ustSinir.getGlobalBounds().height));
			ustSinir.setPosition(0, 0);
			altSinir.setOrigin(sf::Vector2f(0, 0));
			altSinir.setPosition(0, ateslenecekTop.getGlobalBounds().top - ateslenecekTop.getGlobalBounds().height / 2.5);
			tepedeMi = false;
			atilanTopSayisi = 0;
			oyunBittiMi = false;
			silahAci = 0;
			ateslendiMi = false;
			for (int i = 0; i < 4; i++)
			{
				if (i % 2 == 0)
				{
					for (int j = 0; j < 8; j++)
					{
						sf::CircleShape top(yaricap);

						top.setOrigin(sf::Vector2f(yaricap, yaricap));

						top.setPosition(sf::Vector2f(yaricap + j * yaricap * 2, ustSinir.getPosition().y + yaricap + i * (yaricap * sqrt(3))));
						top.setFillColor(renkBelirle(ilkRenkler[(i / 2) * 8 + (i / 2) * 7 + j]));
						toplar.push_back(top);
					}
				}
				else
				{
					for (int j = 0; j < 7; j++)
					{
						sf::CircleShape top(yaricap);
						top.setOrigin(sf::Vector2f(yaricap, yaricap));

						top.setPosition(sf::Vector2f(yaricap + yaricap + j * yaricap * 2, ustSinir.getPosition().y + yaricap + i * (yaricap * sqrt(3))));
						top.setFillColor(renkBelirle(ilkRenkler[((i / 2) + 1) * 8 + ((i / 2) * 7) + j]));
						toplar.push_back(top);
					}
				}
			}

			silah.setOrigin(sf::Vector2f(1, silah.getSize().y));
			silah.setPosition(sf::Vector2f(ateslenecekTop.getPosition().x, ateslenecekTop.getPosition().y));

			oyunbasliyor = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && oyunBittiMi == false)
		{
			if (std::floor(silah.getRotation()) != 80.0f) {
				ok[0].rotate(0.03f);
				silah.rotate(0.03f);
				carkindex += 0.01;
				carktopuindex += 0.01;
				canavar2index += 0.01;
				carkcalisiyor = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && oyunBittiMi == false)
		{
			if (std::ceil(silah.getRotation()) != 280.0f) {
				ok[0].rotate(-0.03f);
				silah.rotate(-0.03f);
				carkindex -= 0.01;
				canavar2index -= 0.01;
				carktopuindex -= 0.01;
				carkcalisiyor = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && oyunBittiMi == true)
		{
			oyunbasliyor = true;
			oyunBittiMi = false;
		}
		sf::Event olay;
		while (pencere.pollEvent(olay))
		{
			if (olay.type == sf::Event::Closed)
			{
				pencere.close();
			}
			if (olay.type == sf::Event::KeyPressed && oyunBittiMi == false)
			{
				if (olay.key.code == sf::Keyboard::Space)
				{
					if (ateslendiMi != true)
					{
						ateslendiMi = true;
						atilanTopSayisi++;
						artisx = cos((90 - silah.getRotation()) * M_PI / 180) * 0.4;
						artisy = sin((90 - silah.getRotation()) * M_PI / 180) * 0.4;
					}
				}
			}
		}
		if (sure.getElapsedTime().asSeconds() >= cerceveSuresi)
		{
			if (ateslendiMi)
			{
				if (topx - ateslenecekTop.getRadius() <= 0)
				{
					artisx *= -1;
					ateslenecekTop.setPosition(yaricap, topy);
				}
				else if (topx + ateslenecekTop.getRadius() >= pencere.getSize().x)
				{
					artisx *= -1;
					ateslenecekTop.setPosition(pencere.getSize().x - yaricap, topy);
				}
				else if (topy <= ustSinir.getPosition().y + yaricap)
				{
					tepedeMi = true;
					sf::CircleShape yeniTop(yaricap);
					yeniTop.setOrigin(yaricap, yaricap);
					yeniTop.setPosition(((((int)topx) / (yaricap * 2)) * (yaricap * 2)) + yaricap, yaricap + ustSinir.getPosition().y);
					yeniTop.setFillColor(ateslenecekTop.getFillColor());
					ateslendiMi = false;
					toplar.push_back(yeniTop);
					for (auto top : toplar)
					{
						if (sqrt(pow(yeniTop.getPosition().y - top.getPosition().y, 2) + pow(yeniTop.getPosition().x - top.getPosition().x, 2)) <= 2 * yaricap)
						{
							/*yoketme*/

							silinecekToplar[toplar.size() - 1] = 2;
							yokEdilecekleriBul(yeniTop);
							toplariSil(ustSinir.getPosition().y);
						}
					}
					topx = pencere.getSize().x / 2;
					topy = pencere.getSize().y - 3 * ateslenecekTop.getRadius();
					ateslenecekTop.setFillColor(renkBelirle(rand() % 4));

				}

				if (tepedeMi == false)
				{
					topx += artisx;
					topy -= artisy;

					for (auto top : toplar)
					{
						if (sqrt(pow(ateslenecekTop.getPosition().y - top.getPosition().y, 2) + pow(ateslenecekTop.getPosition().x - top.getPosition().x, 2)) <= 2 * yaricap - 5)
						{
							ateslendiMi = false;
							satir = round((ateslenecekTop.getPosition().y - yaricap - ustSinir.getPosition().y) / (yaricap * sqrt(3)) + 1);

							if (satir % 2 != 0)
							{
								topx = ((((int)topx) / (yaricap * 2)) * yaricap * 2) + yaricap;
								topy = ustSinir.getPosition().y + yaricap + (satir - 1) * yaricap * sqrt(3);
							}
							else
							{
								topx = ((((yaricap + (int)topx)) / (yaricap * 2)) * (yaricap * 2));
								topy = ustSinir.getPosition().y + yaricap + (satir - 1) * yaricap * sqrt(3);
							}
							sf::CircleShape yeniTop(yaricap);
							yeniTop.setOrigin(yaricap, yaricap);
							yeniTop.setPosition(topx, topy);
							yeniTop.setFillColor(ateslenecekTop.getFillColor());
							toplar.push_back(yeniTop);

							/*yoketme*/
							silinecekToplar[toplar.size() - 1] = 2;
							yokEdilecekleriBul(yeniTop);
							toplariSil(ustSinir.getPosition().y);

							topx = pencere.getSize().x / 2;
							topy = pencere.getSize().y - 3 * ateslenecekTop.getRadius() - 10;
							ateslenecekTop.setFillColor(renkBelirle(rand() % 4));

							break;
						}
					}
				}
			}
			tepedeMi = false;
			ateslenecekTop.setPosition(topx, topy);
			pencere.clear();
			if (ateslendiMi == false) {
				if (atilanTopSayisi == 8)
				{
					ustSinir.move(sf::Vector2f(0, 2 * yaricap));
					for (int i = 0; i < toplar.size(); i++)
					{
						toplar[i].setPosition(toplar[i].getPosition().x, toplar[i].getPosition().y + 2 * yaricap);
					}
					atilanTopSayisi = 0;
				}
			}

			if (anim_patlama)
			{
				for (int i = 0; i < silinenToplar.size(); i++)
				{
					sf::Sprite temp;
					patlamaIndex += 0.003;
					if (silinenToplar.at(i).getFillColor() == sf::Color::Blue)
						temp = toplarSprite[0][(int)patlamaIndex];
					else if (silinenToplar.at(i).getFillColor() == sf::Color::Red)
						temp = toplarSprite[1][(int)patlamaIndex];
					else if (silinenToplar.at(i).getFillColor() == sf::Color::Yellow)
						temp = toplarSprite[2][(int)patlamaIndex];
					else if (silinenToplar.at(i).getFillColor() == sf::Color::Green)
						temp = toplarSprite[3][(int)patlamaIndex];


					temp.setOrigin(sf::Vector2f(temp.getGlobalBounds().height / 2, temp.getGlobalBounds().height / 2));
					temp.scale(sf::Vector2f(2.55, 2.55));
					temp.setPosition(silinenToplar.at(i).getPosition());
					pencere.draw(temp);
				}
			}

			if (patlamaIndex > 13)
			{
				patlamaIndex = 8;
				anim_patlama = false;
				silinenToplar.clear();
			}


			for (int i = 0; i < toplar.size(); i++)
			{
				sf::Sprite temp;
				if (i == toplar.size() - 1 && anim_yapisma)
				{
					yapismaIndex += 0.01;
					if (toplar.at(i).getFillColor() == sf::Color::Blue)
						temp = toplarSprite[0][(int)yapismaIndex];
					else if (toplar.at(i).getFillColor() == sf::Color::Red)
						temp = toplarSprite[1][(int)yapismaIndex];
					else if (toplar.at(i).getFillColor() == sf::Color::Yellow)
						temp = toplarSprite[2][(int)yapismaIndex];
					else if (toplar.at(i).getFillColor() == sf::Color::Green)
						temp = toplarSprite[3][(int)yapismaIndex];

					if (yapismaIndex > 7)
					{
						anim_yapisma = false;
						yapismaIndex = 0;
					}
				}
				else if (toplar.at(i).getFillColor() == sf::Color::Blue)
					temp = toplarSprite[0][0];
				else if (toplar.at(i).getFillColor() == sf::Color::Red)
					temp = toplarSprite[1][0];
				else if (toplar.at(i).getFillColor() == sf::Color::Yellow)
					temp = toplarSprite[2][0];
				else if (toplar.at(i).getFillColor() == sf::Color::Green)
					temp = toplarSprite[3][0];


				temp.setOrigin(sf::Vector2f(temp.getGlobalBounds().height / 2, temp.getGlobalBounds().height / 2));
				temp.scale(sf::Vector2f(2.55, 2.55));
				temp.setPosition(toplar.at(i).getPosition());

				pencere.draw(temp);


				if (toplar.at(i).getPosition().y >= altSinir.getPosition().y - 5)
				{
					oyunBittiMi = true;
				}


			}

			if (toplar.size() == 0)
			{
				oyunBittiMi = true;
			}
			sf::Sprite ateslenecektemp;

			if (ateslenecekTop.getFillColor() == sf::Color::Blue)
				ateslenecektemp = toplarSprite[0][0];
			if (ateslenecekTop.getFillColor() == sf::Color::Red)
				ateslenecektemp = toplarSprite[1][0];
			if (ateslenecekTop.getFillColor() == sf::Color::Yellow)
				ateslenecektemp = toplarSprite[2][0];
			if (ateslenecekTop.getFillColor() == sf::Color::Green)
				ateslenecektemp = toplarSprite[3][0];


			ateslenecektemp.setOrigin(sf::Vector2f(ateslenecektemp.getGlobalBounds().height / 2, ateslenecektemp.getGlobalBounds().height / 2));
			ateslenecektemp.scale(sf::Vector2f(2.50, 2.50));
			ateslenecektemp.setPosition(ateslenecekTop.getPosition());
			sf::Sprite tempcark;
			sf::Sprite tempcarktopu;
			sf::Sprite tempcanavar;
			sf::Sprite tempcanavar2;
			sf::Sprite kaybetmeRengi;
			int tempindex = (int)carkindex;
			int tempcarktopuindex = (int)carktopuindex;
			int tempcanavarindex = (int)canavarindex;
			int tempcanavar2index = (int)canavar2index;
			if (tempindex < 0)
				carkindex = tempindex = 11;
			if (tempindex > 11)
				carkindex = tempindex = 0;

			if (tempcarktopuindex < 0)
				carktopuindex = tempcarktopuindex = 7;
			if (tempcarktopuindex > 7)
				carktopuindex = tempcarktopuindex = 0;

			tempcark = cark[tempindex];
			tempcarktopu = carktopu[tempcarktopuindex];
			tempcark.setOrigin(sf::Vector2f(tempcark.getGlobalBounds().height / 2 + 5, tempcark.getGlobalBounds().height / 2));
			tempcark.setPosition(pencere.getSize().x / 2 - tempcark.getGlobalBounds().height / 2, pencere.getSize().y - 3 * ateslenecekTop.getRadius());
			tempcark.scale(sf::Vector2f(3, 3));

			tempcarktopu.setOrigin(sf::Vector2f(tempcarktopu.getGlobalBounds().height / 2 + 5, tempcarktopu.getGlobalBounds().height / 2));
			tempcarktopu.setPosition((pencere.getSize().x / 2) + 85, pencere.getSize().y - 1 * ateslenecekTop.getRadius());
			tempcarktopu.scale(sf::Vector2f(3, 3));

			if (carkcalisiyor == false)
			{
				canavar2index = 8;
			}
			else
			{
				if (tempcanavar2index < 0)
					canavar2index = tempcanavar2index = 7;
				if (tempcanavar2index > 8)
					canavar2index = tempcanavar2index = 0;
			}


			tempcanavar = canavarlar[0][(int)canavarindex];
			tempcanavar2 = canavarlar[1][(int)canavar2index];

			tempcanavar.setOrigin(sf::Vector2f(tempcanavar.getGlobalBounds().width / 2, tempcanavar.getGlobalBounds().height / 2));
			tempcanavar.scale(sf::Vector2f(3, 3));
			tempcanavar.setPosition((pencere.getSize().x / 2) - pencere.getSize().x / 5, pencere.getSize().y - tempcanavar.getGlobalBounds().height / 2);

			tempcanavar2.setOrigin(sf::Vector2f(tempcanavar2.getGlobalBounds().width / 2, tempcanavar2.getGlobalBounds().height / 2));
			tempcanavar2.scale(sf::Vector2f(3, 3));
			tempcanavar2.setPosition(tempcarktopu.getPosition().x + tempcarktopu.getGlobalBounds().width / 2 - 5, pencere.getSize().y - tempcanavar2.getGlobalBounds().height / 2);


			sf::Sprite tempok;
			tempok = ok[0];
			tempok.setOrigin(silah.getOrigin().x + 30, silah.getOrigin().y - 20);
			tempok.setPosition(silah.getPosition());
			tempok.scale(sf::Vector2f(2.5, 2.5));
			pencere.draw(ustSinir);
			pencere.draw(altSinir);
			pencere.draw(tempcark);

			pencere.draw(tempok);
			pencere.draw(ateslenecektemp);
			pencere.draw(tempcarktopu);
			pencere.draw(tempcanavar);
			pencere.draw(tempcanavar2);
			carkcalisiyor = false;
			if (oyunBittiMi == true)
			{
				for (int i = 0; i < toplar.size(); i++)
				{
					toplar[i].setFillColor(sf::Color{ 169,169,169 });

					kaybetmeRengi = toplarSprite[4][0];

					kaybetmeRengi.setOrigin(kaybetmeRengi.getGlobalBounds().height / 2, kaybetmeRengi.getGlobalBounds().height / 2);
					kaybetmeRengi.setPosition(toplar[i].getPosition());
					kaybetmeRengi.scale(sf::Vector2f(2.50, 2.50));
					pencere.draw(kaybetmeRengi);
				}
				sf::RectangleShape saydam(sf::Vector2f(pencere.getSize().x, pencere.getSize().y));

				sf::Text text;
				sf::Text textreplay;
				text.setFont(font);
				text.setCharacterSize(50);
				if (toplar.size() == 0)
				{

					text.setString("KAZANDIN");
					saydam.setFillColor(sf::Color{ 103, 233, 22,100 });
				}
				else {
					text.setString("OYUN BITTI");
					saydam.setFillColor(sf::Color{ 233, 22, 22,100 });

				}
				text.setFillColor(sf::Color::Red);
				text.setOrigin(sf::Vector2f(0, text.getGlobalBounds().height / 2));
				text.setPosition(sf::Vector2f(20, pencere.getSize().y / 2));
				text.setStyle(sf::Text::Bold);
				textreplay.setFont(font);
				textreplay.setCharacterSize(23);
				textreplay.setString("Tekrar baslamak icin\n    R tusuna basiniz");
				textreplay.setOrigin(sf::Vector2f(0, textreplay.getGlobalBounds().height / 2));
				textreplay.setPosition(sf::Vector2f(18, text.getPosition().y + 100));
				textreplay.setFillColor(sf::Color::Yellow);
				textreplay.setStyle(sf::Text::Bold);
				pencere.draw(saydam);
				pencere.draw(text);
				pencere.draw(textreplay);
			}
			pencere.display();
		}
		else
		{
			sf::sleep(sf::seconds(cerceveSuresi) - sure.getElapsedTime());
		}
	}
}