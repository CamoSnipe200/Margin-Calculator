// Margin Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Caleb Leavesley

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

float PriceAtPurchase;
float TradeBalance;
float PositionProfits;
float Equity;
float CurrentPositionValuation;
float NewPosition;
float TotalPositionValuation;
float PreviousUsedMargin;
float NewMargin;
float ActualTradeBalance;
float Position;
float Leverage;

float TotalMargin;
float MarginPercentage;
float CurrentMarginPercentage;

float PercentChange;

string Input;

float CurrentPrice;
float PriceChange;
float AdjustedTradeBalance;
float TradeBalanceLoss;
float CurrentPositionSize;
float PositionLoss;

bool IsFloat(string MyString);
void GetInitialValues();
void GetResultingValues(int Option);
float GetValidFloat(string Input, float Value);
void DisplayResults();

int main()
{
    GetInitialValues();

    int Option;
    cout << "------------------" << endl;
    cout << "Would you like to: \n1. Input Percent change \n2. Input the current XBT price \n3. Input the target margin percentage" << endl;
    cout << endl << "Option: ";
    cin >> Option;
    while (Option != 1 && Option != 2 && Option != 3)
    {
        cout << "Please enter a valid option: ";
        cin >> Option;
    }

    GetResultingValues(Option);

    DisplayResults();
    
}

void GetInitialValues()
{
    cout << "XBT Price at Purchase: $";
    cin >> Input;
    PriceAtPurchase = GetValidFloat(Input, PriceAtPurchase);

    cout << "TradeBalance: $";
    cin >> Input;
    TradeBalance = GetValidFloat(Input, TradeBalance);

    cout << "Position: $";
    cin >> Input;
    Position = GetValidFloat(Input, Position);

    cout << "Leverage: ";
    cin >> Input;
    Leverage = GetValidFloat(Input, Leverage);

    TotalMargin = Position / Leverage;
    MarginPercentage = TradeBalance / TotalMargin * 100;
}

void GetResultingValues(int Option)
{
    switch (Option)
    {
    case 1:
    {
        

        cout << "Percent loss: %";
        cin >> Input;

        PercentChange = GetValidFloat(Input, PercentChange);
        PercentChange *= .01;
        CurrentPrice = PriceAtPurchase - (PriceAtPurchase * PercentChange);
        PriceChange = PriceAtPurchase - CurrentPrice;
        AdjustedTradeBalance = TradeBalance - (TradeBalance * PercentChange);
        TradeBalanceLoss = TradeBalance - AdjustedTradeBalance;
        CurrentPositionSize = Position - (Position * PercentChange);
        PositionLoss = Position - CurrentPositionSize;
        ActualTradeBalance = AdjustedTradeBalance - PositionLoss;
        CurrentMarginPercentage = ActualTradeBalance / TotalMargin;
        break;
    }
    case 2:
    {
        cout << "Current XBT price: $";
        cin >> Input;
        CurrentPrice = GetValidFloat(Input, CurrentPrice);
        PriceChange = PriceAtPurchase - CurrentPrice;
        PercentChange = 1 - CurrentPrice / PriceAtPurchase;
        AdjustedTradeBalance = TradeBalance - (TradeBalance * PercentChange);
        TradeBalanceLoss = TradeBalance - AdjustedTradeBalance;
        CurrentPositionSize = Position - (Position * PercentChange);
        PositionLoss = Position - CurrentPositionSize;
        ActualTradeBalance = AdjustedTradeBalance - PositionLoss;
        CurrentMarginPercentage = ActualTradeBalance / TotalMargin;
        break;
    }
    case 3:
    {
        cout << "Target margin percentage: %";
        cin >> Input;
        CurrentMarginPercentage = GetValidFloat(Input, CurrentMarginPercentage) * .01;
        float CompleteLoss = (0 - Position) / TotalMargin * 100;
        float MarginPercentDifference = (MarginPercentage - CompleteLoss) * .1;
        float k = 10 / MarginPercentDifference;
        float DeviationWanted = MarginPercentage - CurrentMarginPercentage * 100;
        PercentChange = (k * DeviationWanted) * .01;
        CurrentPrice = PriceAtPurchase - (PriceAtPurchase * PercentChange);
        PriceChange = PriceAtPurchase - CurrentPrice;
        AdjustedTradeBalance = TradeBalance - (TradeBalance * PercentChange);
        TradeBalanceLoss = TradeBalance - AdjustedTradeBalance;
        CurrentPositionSize = Position - (Position * PercentChange);
        PositionLoss = Position - CurrentPositionSize;
        ActualTradeBalance = AdjustedTradeBalance - PositionLoss;
        break;
    }
    default:
        break;
    }
}

float GetValidFloat(string Input, float Value)
{
    while (IsFloat(Input) == false)
    {
        cout << "Please enter a number: ";
        cin >> Input;
    }

    while (stof(Input) < 0)
    {
        cout << "Please enter a value greater than 0: ";
        cin >> Input;
    }

    Value = stof(Input);
    return Value;
}

void DisplayResults()
{
    system("cls");
    cout << left << setw(35) << "XBT price at purchase:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << PriceAtPurchase << endl;
    cout << left << setw(35) << "TradeBalance:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << TradeBalance << endl;
    cout << left << setw(35) << "Position:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << Position << endl;
    cout << left << setw(35) << "Leverage:" << right << setw(1) << " " << setw(10) << setprecision(2) << fixed << Leverage << endl;
    cout << setw(48) << "---------- ---------- ---------- ---------- --------" << endl;
    cout << left << setw(35) << "Margin:" << right << setw(1) << " " << setw(10) << setprecision(2) << fixed << TotalMargin << endl;
    cout << left << setw(35) << "Margin percentage:" << right << setw(1) << "%" << setw(10) << setprecision(2) << fixed << MarginPercentage << endl;
    cout << setw(48) << "---------- ---------- ---------- ---------- --------" << endl;
    cout << left << setw(35) << "Percent loss:" << right << setw(1) << "%" << setw(10) << setprecision(2) << fixed << PercentChange * 100 << endl;
    cout << left << setw(35) << "XBT current price:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << CurrentPrice << endl;
    cout << left << setw(35) << "XBT price loss:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << PriceChange << endl;
    cout << left << setw(35) << "Adjusted TradeBalance:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << AdjustedTradeBalance << endl;
    cout << left << setw(35) << "TradeBalance loss:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << TradeBalanceLoss << endl;
    cout << left << setw(35) << "Current position size:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << CurrentPositionSize << endl;
    cout << left << setw(35) << "Position size loss:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << PositionLoss << endl;
    cout << setw(48) << "---------- ---------- ---------- ---------- --------" << endl;
    cout << left << setw(35) << "Actual TradeBalance:" << right << setw(1) << "$" << setw(10) << setprecision(2) << fixed << ActualTradeBalance << endl;
    cout << left << setw(35) << "Current margin percentage:" << right << setw(1) << "%" << setw(10) << setprecision(2) << fixed << CurrentMarginPercentage * 100 << endl << endl;
}

bool IsFloat(string MyString)
{
    std::istringstream iss(MyString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}
