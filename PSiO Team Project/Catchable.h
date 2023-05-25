#pragma once

class Catchable
{
private:

	//Zmienna okreslajaca czy jest cos na wedce XDDDDD nwm czy to nie powinno po prostu byc w klasie Wand
	bool isCaught = false;
	
protected:
	//szybkosc danej rzeczy, jej sila - z jaka sila bedzie walczyc z graczem, i kwota za jaka gracz bedzie mogl te rybe sprzedac, jej ciezkosc okreslajaca ile mozna przewiesc w lodce
	float speed, strength, value, acceleration, weight;


public:
	
	Catchable();
	~Catchable();

};

