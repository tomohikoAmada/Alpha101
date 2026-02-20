#ifndef ALPHA101_H
#define ALPHA101_H

#include <algorithm>  // Stellt Algorithmen wie sort, upper_bound usw. bereit
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>  // Stellt sliding_window bereit (C++23)
#include <set>
#include <span>
#include <vector>

using namespace std;

// Hilfsfunktion: Ergebnis ausgeben
void print_result(const vector<float>& result);

// Rollende Summe
vector<float> rolling_ts_sum(vector<float> DataFrame, int window);

// Rollender einfacher gleitender Durchschnitt
vector<float> rolling_sma(vector<float> DataFrame, int window);

// Rollende Standardabweichung
vector<float> rolling_stddev(vector<float> DataFrame, int window);

// Korrelationskoeffizient für ein einzelnes Fenster
float correlation(vector<float> a, vector<float> b, int window);

// Rollender Korrelationskoeffizient
vector<float> rolling_correlation(vector<float> a, vector<float> b, int window);

// Kovarianz für ein einzelnes Fenster
float covariance(vector<float> a, vector<float> b, int window);

// Rollende Kovarianz
vector<float> rolling_covariance(vector<float> a, vector<float> b, int window);

// Linearer gewichteter gleitender Durchschnitt (LWMA)
vector<float> decay_linear(vector<float> a, int period = 10);

// ====== Implementierung ======

void print_result(const vector<float>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        if (isnan(result[i])) {
            cout << "NaN";
        } else {
            cout << result[i];
        }
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

vector<float> rolling_ts_sum(vector<float> DataFrame, int window) {
    vector<float> result;
    for (size_t i = 0; i < DataFrame.size(); i++) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; j++) {
                sum += DataFrame[i - j];
            }
            result.push_back(sum);
        }
    }
    return result;
}

vector<float> rolling_sma(vector<float> DataFrame, int window) {
    vector<float> result;
    for (int i = 0; i < DataFrame.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; ++j) {
                sum += DataFrame[i - j];
            }
            float avg = sum / window;
            result.push_back(avg);
        }
    }
    return result;
}

vector<float> rolling_stddev(vector<float> DataFrame, int window) {
    vector<float> result;
    for (int i = 0; i < DataFrame.size(); i++) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; j++) {
                sum += DataFrame[i - j];
            }
            float avg = sum / window;
            sum = 0;
            vector<float> tmp_window;
            for (int j = 0; j < window; j++) {
                tmp_window.push_back(pow((DataFrame[i - j] - avg), 2));
            }
            for (int j = 0; j < tmp_window.size(); j++) {
                sum += tmp_window[j];
            }
            float res = sqrt(sum / (window - 1));
            result.push_back(res);
        }
    }
    return result;
}

float correlation(vector<float> a, vector<float> b, int window) {
    float result = 0;
    float avg_a = rolling_sma(a, a.size()).back();
    float avg_b = rolling_sma(b, b.size()).back();
    vector<float> deviation_a, deviation_b;
    for (int i = 0; i < a.size(); ++i) {
        deviation_a.push_back(a[i] - avg_a);
    }
    for (int i = 0; i < b.size(); ++i) {
        deviation_b.push_back(b[i] - avg_b);
    }
    float SPD = 0;
    for (int i = 0; i < a.size(); ++i) {
        SPD += deviation_a[i] * deviation_b[i];
    }
    float ss_a(0), ss_b(0);
    for (int i = 0; i < deviation_a.size(); ++i) {
        ss_a += deviation_a[i] * deviation_a[i];
    }
    for (int i = 0; i < deviation_b.size(); ++i) {
        ss_b += deviation_b[i] * deviation_b[i];
    }

    result = SPD / sqrt(ss_a * ss_b);

    return result;
}

vector<float> rolling_correlation(vector<float> a, vector<float> b, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            vector<float> window_a, window_b;
            for (int j = 0; j < window; ++j) {
                window_a.push_back(a[i - j]);
                window_b.push_back(b[i - j]);
            }

            float corr = correlation(window_a, window_b, window_a.size());
            result.push_back(corr);
        }
    }

    return result;
}

float covariance(vector<float> a, vector<float> b, int window) {
    float avg_a = rolling_sma(a, a.size()).back();
    float avg_b = rolling_sma(b, b.size()).back();

    vector<float> deviation_a, deviation_b;
    for (int i = 0; i < a.size(); ++i) {
        deviation_a.push_back(a[i] - avg_a);
    }
    for (int i = 0; i < b.size(); ++i) {
        deviation_b.push_back(b[i] - avg_b);
    }

    float SPD = 0;
    for (int i = 0; i < a.size(); ++i) {
        SPD += deviation_a[i] * deviation_b[i];
    }

    return SPD / (a.size() - 1);
}

vector<float> rolling_covariance(vector<float> a, vector<float> b, int window) {
    vector<float> result;
    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            vector<float> window_a, window_b;
            for (int j = 0; j < window; ++j) {
                window_a.push_back(a[i - j]);
                window_b.push_back(b[i - j]);
            }
            float cov = covariance(window_a, window_b, window_a.size());
            result.push_back(cov);
        }
    }

    return result;
}

float rolling_rank(vector<float> a) {
    if (a.empty()) return 0.0f;

    float last_value = a.back();  // Letzten Wert holen

    // Sortieren zur Rangbestimmung (Kopie, Original bleibt unverändert)
    sort(a.begin(), a.end());

    // Bereich aller Werte gleich last_value bestimmen
    // lower_bound: erste Position, die nicht kleiner als last_value ist
    // upper_bound: erste Position, die größer als last_value ist
    auto lower = lower_bound(a.begin(), a.end(), last_value);
    auto upper = upper_bound(a.begin(), a.end(), last_value);

    // Durchschnittsrang berechnen
    // Beispiel: [1, 2, 3, 3, 3] – drei 3er belegen Plätze 3,4,5 (Index 2,3,4)
    // lower-Index=2, upper-Index=5
    // Rangbereich: 3 bis 5, Durchschnittsrang=(3+4+5)/3=4.0
    size_t first_rank = distance(a.begin(), lower) + 1;  // Rang des ersten gleichen Wertes
    size_t last_rank = distance(a.begin(), upper);       // Rang des letzten gleichen Wertes
    float avg_rank = (first_rank + last_rank) / 2.0f;    // Durchschnittsrang

    return avg_rank;
}

// Optimierte Version von rolling_rank: verwendet span, um temporäre Vektoren zu
// vermeiden. span ist ein C++20-Feature – eine reine Datenansicht ohne Besitz
// oder Kopie
float rolling_rank(span<const float> data) {
    if (data.empty()) return 0.0f;

    float last_value = data.back();

    // Temporären Vektor zum Sortieren erstellen (unvermeidlich, da Sortierung
    // erforderlich)
    vector<float> sorted(data.begin(), data.end());
    sort(sorted.begin(), sorted.end());

    auto lower = lower_bound(sorted.begin(), sorted.end(), last_value);
    auto upper = upper_bound(sorted.begin(), sorted.end(), last_value);

    size_t first_rank = distance(sorted.begin(), lower) + 1;
    size_t last_rank = distance(sorted.begin(), upper);
    float avg_rank = (first_rank + last_rank) / 2.0f;

    return avg_rank;
}

vector<float> ts_rank(vector<float> a, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            // Erste window-1 Positionen geben NaN zurück
            result.push_back(NAN);
        } else {
            // Fenster [i-window+1, i] extrahieren, enthält window Elemente
            // C++ Bereichskonstruktor ist [first, last), daher Endposition i+1
            vector<float> tmp(&a[i - window + 1], &a[i + 1]);
            result.push_back(rolling_rank(tmp));

            // Vereinfacht schreibbar als
            // result.push_back(rolling_rank(vector<float>(&a[i - window + 1], &a[i +
            // 1])));
        }
    }

    return result;
}

// Mit span optimierte Version: vermeidet Erstellung temporärer Vektoren
vector<float> ts_rank_optimized(const vector<float>& a, int window) {
    size_t n = a.size();
    vector<float> result(n);
    for (size_t i = 0; i < n; ++i)
        result[i] = i + 1 < window ? NAN : rolling_rank(span<const float>(&a[i - window + 1], window));
    return result;
}

// Hochoptimierte Version: gleitendes Fenster + multiset, Komplexität: O(n × log
// window) statt O(n × window × log window)
vector<float> ts_rank_ultra(const vector<float>& a, int window) {
    size_t n = a.size();
    vector<float> result(n);

    multiset<float> ordered_window;  // Automatisch sortiert

    for (size_t i = 0; i < n; ++i) {
        // Neues Element zum Fenster hinzufügen
        ordered_window.insert(a[i]);

        // Ältestes Element entfernen, wenn Fenster voll ist
        if (i >= window) {
            // find() gibt das erste passende Element zurück, dann löschen
            ordered_window.erase(ordered_window.find(a[i - window]));
        }

        // Rang berechnen
        if (i + 1 < window) {
            result[i] = NAN;
        } else {
            float last_value = a[i];

            // lower_bound: erste Position, die nicht kleiner als last_value ist
            // upper_bound: erste Position, die größer als last_value ist
            auto lower = ordered_window.lower_bound(last_value);
            auto upper = ordered_window.upper_bound(last_value);

            // Durchschnittsrang berechnen
            size_t rank_start = distance(ordered_window.begin(), lower) + 1;
            size_t rank_end = distance(ordered_window.begin(), upper);

            result[i] = (rank_start + rank_end) / 2.0f;
        }
    }

    return result;
}

float rolling_prod(vector<float> a) {
    float result = 1;

    for (int i = 0; i < a.size(); ++i) {
        result *= a[i];
    }

    return result;
}

vector<float> product(vector<float> a, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(rolling_prod(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

vector<float> ts_min(vector<float> a, int window) {
    vector<float> result;

    auto getminval = [](vector<float> aa) {
        sort(aa.begin(), aa.end());
        return aa.front();
    };

    // Alternative ohne auto: Funktionszeiger auf Lambda mit Parameter
    // float (*getminval_without_auto)(vector<float>) = [](vector<float> aa) {
    //     sort(aa.begin(), aa.end());
    //     return aa.front();
    // };

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(getminval(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

vector<float> ts_max(vector<float> a, int window) {
    vector<float> result;

    auto getmaxval = [](vector<float> aa) {
        sort(aa.begin(), aa.end());
        return aa.back();
    };

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(getmaxval(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

vector<float> delta(vector<float> a, int period) {
    vector<float> result;
    for (int i = 0; i < a.size(); ++i) {
        if (i < period) {
            result.push_back(NAN);
        } else {
            result.push_back(a[i] - a[i - period]);
        }
    }

    return result;
}

vector<float> delay(vector<float> a, int period) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i < period) {
            result.push_back(NAN);
        } else {
            result.push_back(a[i - period]);  // Korrektur: verzögerter Wert wird
                                              // zurückgegeben, keine Differenz
        }
    }

    return result;
}

vector<float> alpha_rank(vector<float> a) {
    size_t n = a.size();
    if (n == 0) return {};

    vector<float> result(n);

    vector<float> idx(a.size());
    iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(), [a](int i, int j) { return a[i] < a[j]; });

    int i = 0;
    while (i < a.size()) {
        int j = i;

        while (j < a.size() && a[idx[i]] == a[idx[j]]) {
            j++;
        }

        float avg_rank = (i + 1 + j) / 2.0f;

        float pct_rank = avg_rank / n;

        for (int k = i; k < j; ++k) {
            result[idx[k]] = pct_rank;
        }

        i = j;
    }

    return result;
}

vector<float> scale(vector<float> a, float k = 1.0f) {
    float sum = 0;
    for (size_t i = 0; i < a.size(); i++) {
        sum += std::abs(a[i]);
    }

    vector<float> result;

    for (size_t i = 0; i < a.size(); i++) {
        result.push_back(a[i] * k / sum);
    }

    return result;
}

inline vector<int> ts_argmax(vector<float> a, int window = 10) {
    vector<int> result(a.size(), 0);

    for (size_t i = window - 1; i < a.size(); i++) {
        int maxIdx = 0;
        for (int j = 1; j < window; j++) {
            if (a[i - window + 1 + j] > a[i - window + 1 + maxIdx]) {
                maxIdx = j;
            }
        }
        result[i] = maxIdx + 1;  // 1-indexed
    }

    return result;
}

inline vector<int> ts_argmin(vector<float> a, int window = 10) {
    vector<int> result(a.size(), 0);

    for (size_t i = window - 1; i < a.size(); i++) {
        int minIdx = 0;
        for (int j = 1; j < window; j++) {
            if (a[i - window + 1 + j] < a[i - window + 1 + minIdx]) {
                minIdx = j;
            }
        }
        result[i] = minIdx + 1;  // 1-indexed
    }

    return result;
}

inline vector<float> decay_linear(vector<float> a, int period) {
    size_t n = a.size();
    vector<float> result(n, NAN);

    // divisor = 1+2+...+period，用等差数列公式计算
    float divisor = period * (period + 1) / 2.0f;

    // 预计算权重：y[k] = (k+1)/divisor，k=0 对应窗口最旧元素，k=period-1
    // 对应最新元素
    vector<float> y(period);
    for (int k = 0; k < period; ++k) {
        y[k] = (k + 1) / divisor;
    }

    for (size_t i = period - 1; i < n; ++i) {
        float val = 0.0f;
        for (int k = 0; k < period; ++k) {
            val += a[i - period + 1 + k] * y[k];
        }
        result[i] = val;
    }

    return result;
}

#endif  // ALPHA101_H
