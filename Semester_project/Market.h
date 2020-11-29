#pragma once
#include "Warehouse.h"

class Market {
private:
	static float WheatPrice;
	static Warehouse* Wh;
public:
	static void setWheatPrice(float wheatPrice) {
		WheatPrice = wheatPrice;
	}

	static float getWheatPrice() { return WheatPrice; }

	static bool buyWheat(float kilos) {
		float resultPrice = kilos * WheatPrice;
		if (Wh->getCoins() >= resultPrice) {
			float whResultCoins = Wh->getCoins();
			whResultCoins -= resultPrice;
			float whResultWheat = Wh->getWheat();
			whResultWheat += kilos;
			Wh->setCoins(whResultCoins);
			Wh->setWheat(whResultWheat);
		}
	}

	static bool buyField(int size) {
		float price = size * 10;
		if (price <= Wh->getCoins()) {
			float resultCoins = (Wh->getCoins()) - price;
			Wh->setCoins(resultCoins);
			return true;
		}
		else return false;
	}

	static void sellWheat() {
		float resultCoins = (Wh->getWheat() * WheatPrice) + Wh->getCoins();
		Wh->setWheat(0);
		Wh->setCoins(resultCoins);
	}
};

float Market::WheatPrice = 0.5;
Warehouse* Market::Wh = Warehouse::GetInstance();