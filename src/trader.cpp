#include "trader.h"

Trader::Trader(int id, double initialPnl, double tolerance)
    : trader_id(id), pnl(initialPnl), risk_tolerance(tolerance) {}

int Trader::getTraderId() const {
    return trader_id;
}

double Trader::getPnl() const {
    return pnl;
}

void Trader::setPnl(double newPnl) {
    pnl = newPnl;
}

double Trader::getRiskTolerance() const {
    return risk_tolerance;
}

void Trader::setRiskTolerance(double newRiskTolerance) {
    risk_tolerance = newRiskTolerance;
}
