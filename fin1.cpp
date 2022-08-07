#include <iostream>
#include <string>
#include <fstream>
#include<vector>
#include<algorithm>

using namespace std;

string WEATHER, WEATHER_ES, DAY;
int TEMPERATURE_H=0;
int TEMPERATURE_L = 0;
vector<string> Opt;


class Product {
	string name;
	string weather;
	string weather_es;
	string day;
	int temperature_h = 0;
	int temperature_l = 0;
	

public:
	void setName(const string& newName) { name = newName; }
	void setWeather(const string& newWeather) { weather = newWeather; }
	void setWeather_es(const string& newWeather_es) { weather_es = newWeather_es; }
	void setDay(const string& newDay) { day = newDay; }
	void setTemperature_h(int newTemperature_h) { temperature_h = newTemperature_h; }
	void setTemperature_l(int newTemperature_l) { temperature_l = newTemperature_l; }
	void eva();
};

class Suitable {
	string name;
	float a = 0;

public:
	void setName(const string& newName) { name = newName; }
	void setA(float newA) { a = newA; }
	void getName() { cout << "\t" << name << endl; }
	int getA() { return a; }
};
vector<Suitable> Suit;

void Product::eva() {
	if ((weather == "��" && WEATHER == "��") || (weather == "�䕗" && WEATHER == "�䕗")||(weather_es == "��"&& WEATHER_ES == "��")|| (weather_es == "�䕗" && WEATHER_ES == "�䕗")) {
		Opt.emplace_back(name);
		return;
	}
	float a = 0;
	int b = 0;
	b =temperature_h - temperature_l;
	if (weather == WEATHER) a += 10;
	if (day == DAY) a += 10;
	if ((temperature_h>=TEMPERATURE_H)&&(temperature_l<=TEMPERATURE_L)) a += 20;
	if ((temperature_h >= TEMPERATURE_H) && (temperature_l <= TEMPERATURE_H) && (temperature_l > TEMPERATURE_L)) a += (10 + 100 / b);
	if ((temperature_h >= TEMPERATURE_L) && (temperature_l <= TEMPERATURE_L) && (temperature_h < TEMPERATURE_H)) a += (10 + 100 / b);
	if ((temperature_h > TEMPERATURE_H) && (temperature_l < TEMPERATURE_L)) a += (15 + 100 / b);
	if ((weather == "��" && WEATHER == "��")|| (weather == "��" && WEATHER == "��"))  a += 8;
	if ((day == "�x�O��" && DAY == "�x��") || (day == "�x��" && DAY == "�x�O��")) a += 8;
	if (weather == "��")  a += 5 ;
	if (day == "��") a += 5;
	if (a >= 30) {
		Suit.emplace_back();
		Suit[Suit.size() - 1].setName(name);
		Suit[Suit.size() - 1].setA(a);
		return;
	}
}

int main() {
	vector<Product> tendency;
	

	ifstream infile("list1.dat");
	
	string name, weather, weather_es, day;
	int temperature_h, temperature_l;
	
	while (infile >> name >> weather >> weather_es >> day >> temperature_h >> temperature_l) {
		tendency.emplace_back();
		tendency[tendency.size() - 1].setName(name);
		tendency[tendency.size() - 1].setWeather(weather);
		tendency[tendency.size() - 1].setWeather_es(weather_es);
		tendency[tendency.size() - 1].setDay(day);
		tendency[tendency.size() - 1].setTemperature_h(temperature_h);
		tendency[tendency.size() - 1].setTemperature_l(temperature_l);
	}
	infile.close();
	
	cout << "�V�C�ɉ������������ߏ��i��\�����܂�" << endl; 
	cout << "�V�C�́@���@�܂�@�J�@�䕗�@��@�̂ǂ�ł����B�K�؂Ȃ��̂���͂�Enter�L�[�������Ă�������" << endl;
	cin >> WEATHER;
	cout << "\n��1�T�Ԃ̊Ԃɑ䕗�܂��͐�\��͂���܂����B�䕗�@��@���@�̂�������K�؂Ȃ��̂���͂�Enter�L�[�������Ă�������" << endl;
	cin >> WEATHER_ES;
	cout << "\n�x�O���@�x���@�����@�̂ǂ�ł����B�K�؂Ȃ��̂���͂�Enter�L�[�������Ă�������" << endl;
	cin >> DAY;
	cout << "\n�ō��C���͉����ł����B���L���������������œ��͂�Enter�L�[�������Ă�������" << endl;
	cin >> TEMPERATURE_H;
	cout << "\n�Œ�C���͉����ł����B���L���������������œ��͂�Enter�L�[�������Ă�������" << endl;
	cin >> TEMPERATURE_L;


	for (auto i = 0; i < tendency.size(); i++) { tendency[i].eva(); }
	sort(Suit.begin(), Suit.end(), [](Suitable& x, Suitable& y) {return x.getA() > y.getA(); });

	if (Opt.size() != 0) {
		cout << "\n�����Ǝ��v�����܂�I" << endl;
		for (auto x : Opt) cout << "\t" << x << endl;
	}
	cout << "\n�������߁I����؏��i" << endl;
	for (auto i = 0; (i < Suit.size())&&(i <= 4); i++) { Suit[i].getName(); }
}