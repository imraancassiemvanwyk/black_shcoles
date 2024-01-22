// Black-Shcoles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <math.h>



class black_scholes
{

public:

	double volatility;
	double strike_price;
	double stock_price;
	double time_till_maturity;
	double risk_free_rate;
	double dividends;

	double normal_cdf(double x)
	{
		double val = 0.5;
		for (int n = 0; n < 34; n++)
		{
			val += (1 / std::sqrt(2 * M_PI)) *
				(std::pow(-1, n) * std::pow(x, ((2 * n) + 1))) /
				(((2 * n) + 1) * std::pow(2, n) * factorial(n));
		}
		return val;
	}

	double normal_probability_density(double x)
	{
		return ((1 / std::sqrt(2 * M_PI) *
			std::exp(-1 * (x * x) * 0.5)));
	}


	int factorial(int x)
	{
		int val = 1;
		if ((x == 0) || (x == 1))
		{
			return val;
		}
		else
		{
			for (int i = 1; i < x; i++)
			{
				val *= (i + 1);
			}
			return val;
		}

	}

	double d1()
	{
		return (1 / (volatility * std::sqrt(time_till_maturity))) *
			(log(stock_price / strike_price) +
				((risk_free_rate-dividends + (volatility * volatility * 0.5)) * (time_till_maturity)));
	}

	double d2()
	{
		return (d1()
			- (volatility * std::sqrt(time_till_maturity)));
	}

	double call_price()
	{
		return ((std::exp((- 1 * dividends)*time_till_maturity) * stock_price * normal_cdf(d1()))
			- (normal_cdf(d2())
				* strike_price * std::exp((-1 * risk_free_rate) * time_till_maturity)));
	}

	double put_price()
	{
		return ((strike_price * std::exp((-1 * risk_free_rate) * time_till_maturity)*normal_cdf(-1 * d2()))
			-(stock_price*std::exp((-1*dividends)*time_till_maturity)*normal_cdf(-1*d1())));
	}

	double gamma()
	{
		return ((normal_probability_density(d1())*std::exp((-1 * dividends) * time_till_maturity))
			/(stock_price*volatility*std::sqrt(time_till_maturity)));
	}

	double vega()
	{
		return  std::exp((-1*dividends)*time_till_maturity) * stock_price * std::sqrt(time_till_maturity)
			* normal_probability_density(d1());
	}

	double call_delta()
	{
		return (std::exp((-1*dividends)*time_till_maturity)*normal_cdf(d1()));
	}

	double put_delta()
	{
		return (std::exp((-1 * dividends) * time_till_maturity) * (normal_cdf(d1()) - 1));
	}

	double call_rho()
	{
		return (strike_price * time_till_maturity*std::exp((-1*risk_free_rate)*time_till_maturity)
			 * normal_cdf(d2()));
	}

	double put_rho()
	{
		return  strike_price * time_till_maturity * std::exp((-1 *risk_free_rate) * time_till_maturity)
			* (- 1) * normal_cdf(-1 * d2());
	}

	double call_theta()
	{
		double term1 = (std::exp((-1 * dividends) * time_till_maturity) * stock_price * volatility
			* normal_probability_density(d1()))
			/(2*std::sqrt(time_till_maturity));
		double term2 = risk_free_rate * strike_price *std::exp((-1*risk_free_rate)*time_till_maturity)
			* normal_cdf(d2());
		double term3 = dividends * stock_price * std::exp((-1 * dividends) * time_till_maturity)
			* normal_cdf(d1());
		return -1*((-1 * term1) - term2 + term3);
	}

	double put_theta()
	{
		double term1 = ((stock_price * volatility)
			* normal_probability_density(d1()))
			/ (2 * std::sqrt(time_till_maturity));
		double term2 = risk_free_rate * strike_price * std::exp((-1 * risk_free_rate) * time_till_maturity)
			* normal_cdf(-1 * d2());
		double term3 = dividends * stock_price * std::exp((-1 * dividends) * time_till_maturity)
			* normal_cdf(-1 * d1());
		return -1*((term1 * -1) + term2 - term3);
	}
};



int main()
{
	black_scholes bs;
	bs.volatility = 0.15;
	bs.strike_price = 250;
	bs.stock_price = 300;
	bs.time_till_maturity = 1;
	bs.risk_free_rate = 0.03;
	bs.dividends = 0.05;
	std::cout << bs.call_price()<<std::endl;
	std::cout << bs.put_price() << std::endl;
	std::cout << bs.call_delta() << std::endl;
	std::cout << bs.put_delta() << std::endl;
	std::cout << bs.gamma() << std::endl;
	std::cout << bs.vega() << std::endl;
	std::cout << bs.call_rho() << std::endl;
	std::cout << bs.put_rho() << std::endl;
	std::cout << bs.call_theta() << std::endl;
	std::cout << bs.put_theta() << std::endl;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
