#ifndef ALPHA101_H
#define ALPHA101_H

#include "Alpha101Utils.h"

// ====== Alpha-Faktor-Implementierungen ======

// Alpha#1: (rank(Ts_ArgMax(SignedPower(((returns < 0) ? stddev(returns, 20) : close), 2.), 5)) - 0.5)
inline vector<float> alpha001(const vector<float>& close, const vector<float>& returns) {
    size_t n = close.size();

    // Schritt 1: Rollende Standardabweichung der Renditen (Fenster=20)
    vector<float> std_ret = rolling_stddev(returns, 20);

    // Schritt 2 & 3: inner = (returns < 0) ? stddev(returns, 20) : close
    //                inner_sq = SignedPower(inner, 2) = inner^2
    // Warm-up: Solange stddev noch NAN ist (erste 19 Tage), bleibt inner_sq NAN
    vector<float> inner_sq(n, NAN);
    for (size_t i = 0; i < n; ++i) {
        if (isnan(std_ret[i])) continue;
        float val = (returns[i] < 0.0f) ? std_ret[i] : close[i];
        inner_sq[i] = val * val;
    }

    // Schritt 4: ts_argmax(inner_sq, 5) — NAN wird weitergeleitet
    vector<float> argmax_f = ts_argmax(inner_sq, 5);

    // Schritt 5: Perzentilrang - 0.5
    vector<float> result = alpha_rank(argmax_f);
    for (size_t i = 0; i < n; ++i)
        if (!isnan(result[i])) result[i] -= 0.5f;

    return result;
}

#endif  // ALPHA101_H
