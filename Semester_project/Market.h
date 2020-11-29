#pragma once
#include "Warehouse.h"

class Market {
private:
	float WheatPrice;
	Warehouse* Wh;
public:
	Market() {
		Wh = Warehouse::GetInstance();
		WheatPrice = 0.5;
	}

	void setWheatPrice(float wheatPrice) {
		WheatPrice = wheatPrice;
	}

	float getWheatPrice() { return WheatPrice; }

	bool buyWheat(float kilos) {
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

	bool buyField(int size) {
		float price = size * 10;
		if (price <= Wh->getCoins()) {
			float resultCoins = (Wh->getCoins()) - price;
			Wh->setCoins(resultCoins);
			return true;
		}
		else return false;
	}

	void sellWheat() {
		float resultCoins = (Wh->getWheat() * WheatPrice) + Wh->getCoins();
		Wh->setWheat(0);
		Wh->setCoins(resultCoins);
	}

	~Market() {}
};