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
	if ((weather == "雪" && WEATHER == "雪") || (weather == "台風" && WEATHER == "台風")||(weather_es == "雪"&& WEATHER_ES == "雪")|| (weather_es == "台風" && WEATHER_ES == "台風")) {
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
	if ((weather == "晴" && WEATHER == "曇")|| (weather == "曇" && WEATHER == "晴"))  a += 8;
	if ((day == "休前日" && DAY == "休日") || (day == "休日" && DAY == "休前日")) a += 8;
	if (weather == "無")  a += 5 ;
	if (day == "無") a += 5;
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
	
	cout << "天気に応じたおすすめ商品を表示します" << endl; 
	cout << "天気は　晴　曇り　雨　台風　雪　のどれですか。適切なものを入力しEnterキーを押してください" << endl;
	cin >> WEATHER;
	cout << "\n先1週間の間に台風または雪予報はありますか。台風　雪　無　のうちから適切なものを入力しEnterキーを押してください" << endl;
	cin >> WEATHER_ES;
	cout << "\n休前日　休日　平日　のどれですか。適切なものを入力しEnterキーを押してください" << endl;
	cin >> DAY;
	cout << "\n最高気温は何℃ですか。℃記号を除いた整数で入力しEnterキーを押してください" << endl;
	cin >> TEMPERATURE_H;
	cout << "\n最低気温は何℃ですか。℃記号を除いた整数で入力しEnterキーを押してください" << endl;
	cin >> TEMPERATURE_L;


	for (auto i = 0; i < tendency.size(); i++) { tendency[i].eva(); }
	sort(Suit.begin(), Suit.end(), [](Suitable& x, Suitable& y) {return x.getA() > y.getA(); });

	if (Opt.size() != 0) {
		cout << "\nきっと需要が高まる！" << endl;
		for (auto x : Opt) cout << "\t" << x << endl;
	}
	cout << "\nおすすめ！売れ筋商品" << endl;
	for (auto i = 0; (i < Suit.size())&&(i <= 4); i++) { Suit[i].getName(); }
}