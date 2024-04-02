#ifndef TRADER_H
#define TRADER_H

class Trader {
private:
    int trader_id;
    double pnl;
    double risk_tolerance;

public:
    Trader(int id, double pnl, double risk_tolerance);

    int getTraderId() const;
    double getPnl() const;
    void setPnl(double newPnl);
    double getRiskTolerance() const;
    void setRiskTolerance(double newRiskTolerance);
};

#endif // TRADER_H
