#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Currency
{
protected:
	string name;
	double price;
	double amount;
public:
	Currency() {
		name = "";
		price = 0;
		amount = 0;
	}
	string getName() const {
		return name;
	}
	double getPrice() const {
		return price;
	}
	double getAmount() const {
		return amount;
	}

    friend istream &operator>>(istream &in, Currency &bet);
};

istream &operator>>(istream &in, Currency &bet) {
	string temp;
	in >> temp;
	if(temp.empty()) throw "Name is empty!";
	double tPrice, tAmount;
	in >> tPrice >> tAmount;
	if(tPrice < 0 || tAmount < 0) throw "price or amount is empty!";
	bet.name = temp;
	bet.price = tPrice;
	bet.amount = tAmount;
	return in;
}

class Portfolio
{
protected:
	string name;
	vector<Currency> currencies;
public:
    double calculateTotalPortfolioBalance() const
    {
	double result = 0;
	for(auto &curr : currencies) {
		result += curr.getAmount() * curr.getPrice();
	}
	return result;
    }

    double estimateReturn() const
    {
	    return calculateTotalPortfolioBalance() * getRisk();
    }

    double estimateReturnAfterTax() const
    {
	    return estimateReturn() * getTax();
    }

    virtual double getTax() const = 0;
    virtual double getRisk() const = 0;

    string getName() const {
	return name;
    }
    vector<Currency>& getCurrencies() {
	return currencies;
    }

    friend istream &operator>>(istream &in, Portfolio *portfolio)
    {
	string temp_name;
	in >> temp_name;
	if(temp_name.empty()) throw "Portfolio name is empty!";
	portfolio->name = temp_name;
	return in;
    }
};

class CryptoPortfolio : public Portfolio {
	double getRisk() const {
		return 1000 / 100;
	}
	double getTax() const {
		return 0.9;
	}
};

class StocksPortfolio : public Portfolio {
	double getRisk() const {
		return 0.1;
	}
	double getTax() const {
		return 1;
	}
};

int main()
{
    vector<Portfolio *> arr;
    ifstream file("portfolio.txt");
    if(!file) throw "Cannot open file!";
    int index = 0;
    	while(1) {
		string type;
		file >> type;
		Portfolio *temp;
		if(type == "C") temp = new CryptoPortfolio();
		if(type == "S") temp = new StocksPortfolio();
			file >> arr.emplace_back(temp);
			int num = 0;
			file >> num;
			for(unsigned int i = 0; i < num; i++) {
				Currency *temp =  new Currency();
				file >> *temp;
				arr[i]->getCurrencies().push_back(*temp);
			}
	}
    return 0;
}
