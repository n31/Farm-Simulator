#pragma once

class Warehouse {
private:
	float Coins;
	float Wheat;
public:
	Warehouse() {
		this->Coins = 0;
		this->Wheat = 0;
	}

	void setCoins(float coins) {
		Coins = coins;
	}

	void incrCoins() {
		Coins++;
	}

	void setWheat(float wheat) {
		Wheat = wheat;
	}

	void incrWheat() {
		Wheat++;
	}

	float getCoins() { return Coins; }

	float getWheat() { return Wheat; }

	~Warehouse() {}
};