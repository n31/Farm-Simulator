#pragma once

class Warehouse {
private:
	float Coins;
	float Wheat;
	Warehouse() {
		this->Coins = 0;
		this->Wheat = 0;
	}
	static Warehouse* warehouse_;
public:
	static Warehouse* GetInstance() {
		if (warehouse_ == nullptr) {
			warehouse_ = new Warehouse();
		}
		return warehouse_;
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

Warehouse* Warehouse::warehouse_ = nullptr;