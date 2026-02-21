#ifndef ALPHA101UTILS_H
#define ALPHA101UTILS_H

#include <algorithm>  // Stellt Algorithmen wie sort, upper_bound usw. bereit
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>  // Stellt sliding_window bereit (C++23)
#include <set>
#include <span>
#include <vector>

using namespace std;

// ====== Deklarationen ======

// Hilfsfunktion: Ergebnis ausgeben
void print_result(const vector<float>& result);

// Rollende Summe
vector<float> rolling_ts_sum(vector<float> DataFrame, int window);

// Rollender einfacher gleitender Durchschnitt
vector<float> rolling_sma(vector<float> DataFrame, int window);

// Rollende Standardabweichung
vector<float> rolling_stddev(const vector<float>& DataFrame, int window);

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

vector<float> rolling_stddev(const vector<float>& DataFrame, int window) {
    int n = (int)DataFrame.size();
    vector<float> result(n, NAN);
    if (window <= 1 || n < window) return result;

    // 初始化第一个窗口的 sum 和 sum_sq
    float sum = 0.0f, sum_sq = 0.0f;
    for (int i = 0; i < window; ++i) {
        sum    += DataFrame[i];
        sum_sq += DataFrame[i] * DataFrame[i];
    }
    // 第一个有效输出
    {
        float var = (sum_sq - sum * sum / window) / (window - 1);
        result[window - 1] = std::sqrt(var > 0.0f ? var : 0.0f);
    }
    // 滑动：每步 O(1)，仅加入新元素、移出旧元素
    for (int i = window; i < n; ++i) {
        float x_new = DataFrame[i];
        float x_old = DataFrame[i - window];
        sum    += x_new - x_old;
        sum_sq += x_new * x_new - x_old * x_old;
        float var = (sum_sq - sum * sum / window) / (window - 1);
        result[i] = std::sqrt(var > 0.0f ? var : 0.0f);
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

inline vector<float> delay(vector<float> a, int period) {
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

inline vector<float> alpha_rank(const vector<float>& a) {
    size_t n = a.size();
    vector<float> result(n, NAN);

    // NAN-Werte ausschließen: std::sort mit NAN ist undefiniertes Verhalten
    vector<size_t> valid_idx;
    for (size_t i = 0; i < n; ++i)
        if (!isnan(a[i])) valid_idx.push_back(i);

    size_t m = valid_idx.size();
    if (m == 0) return result;

    // valid_idx 原地排序，省去 sorted_idx 的额外拷贝和堆分配
    sort(valid_idx.begin(), valid_idx.end(), [&](size_t i, size_t j) { return a[i] < a[j]; });

    // Perzentilrang mit Mittelwert bei Gleichstand zuweisen
    size_t i = 0;
    while (i < m) {
        size_t j = i;
        while (j < m && a[valid_idx[i]] == a[valid_idx[j]]) j++;
        float avg_rank = (i + 1 + j) / 2.0f;
        float pct_rank = avg_rank / (float)m;
        for (size_t k = i; k < j; ++k) result[valid_idx[k]] = pct_rank;
        i = j;
    }

    return result;
}

/**
 * @brief alpha_rank 的 span 重载，避免调用方额外拷贝
 *
 * 与 vector 版语义完全相同：对输入数据做百分位截面排名（NaN 保留）。
 * 供截面因子函数直接传入连续内存视图，无需构造临时 vector。
 *
 * @param a      输入数据的只读视图（连续内存）
 * @return       与 a 等长的排名结果，NaN 位置保持 NaN，有效值域 (0, 1]
 */
inline vector<float> alpha_rank(span<const float> a) {
    size_t n = a.size();
    vector<float> result(n, NAN);

    vector<size_t> valid_idx;
    for (size_t i = 0; i < n; ++i)
        if (!isnan(a[i])) valid_idx.push_back(i);

    size_t m = valid_idx.size();
    if (m == 0) return result;

    // valid_idx 原地排序，省去 sorted_idx 的额外拷贝和堆分配
    sort(valid_idx.begin(), valid_idx.end(), [&](size_t i, size_t j) { return a[i] < a[j]; });

    size_t i = 0;
    while (i < m) {
        size_t j = i;
        while (j < m && a[valid_idx[i]] == a[valid_idx[j]]) j++;
        float avg_rank = (i + 1 + j) / 2.0f;
        float pct_rank = avg_rank / (float)m;
        for (size_t k = i; k < j; ++k) result[valid_idx[k]] = pct_rank;
        i = j;
    }

    return result;
}

/**
 * @brief alpha_rank 高性能重载：零内部堆分配，含插入排序小规模快速路径
 *
 * 与其他重载语义完全相同，但所有临时存储由调用方提供，可在循环中复用。
 * 适合在 T 次截面循环中调用：在循环外声明 out/idx_buf，循环内传入。
 *
 * @param a       输入数据的只读视图（连续内存）
 * @param out     输出缓冲区（与 a 等长，函数负责完整写入，无需预初始化）
 * @param idx_buf 调用方提供的临时索引缓冲区，循环内复用；建议循环外 reserve(n)
 *
 * 排序策略：
 *   m <= 32  → 插入排序（O(m²) 但常数极小，分支预测友好）
 *   m >  32  → std::sort（introsort，O(m log m)）
 */
inline void alpha_rank(span<const float> a, span<float> out, vector<size_t>& idx_buf) {
    size_t n = a.size();
    fill(out.begin(), out.end(), NAN);

    idx_buf.clear();
    for (size_t i = 0; i < n; ++i)
        if (!isnan(a[i])) idx_buf.push_back(i);

    size_t m = idx_buf.size();
    if (m == 0) return;

    if (m <= 32) {
        // 插入排序：小规模时避免 introsort 的函数调用和递归开销
        for (size_t i = 1; i < m; ++i) {
            size_t key = idx_buf[i];
            float key_val = a[key];
            size_t j = i;
            while (j > 0 && a[idx_buf[j - 1]] > key_val) {
                idx_buf[j] = idx_buf[j - 1];
                --j;
            }
            idx_buf[j] = key;
        }
    } else {
        sort(idx_buf.begin(), idx_buf.end(), [&](size_t i, size_t j) { return a[i] < a[j]; });
    }

    size_t i = 0;
    while (i < m) {
        size_t j = i;
        while (j < m && a[idx_buf[i]] == a[idx_buf[j]]) j++;
        float avg_rank = (i + 1 + j) / 2.0f;
        float pct_rank = avg_rank / (float)m;
        for (size_t k = i; k < j; ++k) out[idx_buf[k]] = pct_rank;
        i = j;
    }
}

inline vector<float> scale(vector<float> a, float k = 1.0f) {
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

inline vector<float> ts_argmax(const vector<float>& a, int window = 10) {
    size_t n = a.size();
    vector<float> result(n, NAN);

    for (size_t i = window - 1; i < n; ++i) {
        bool has_nan = false;
        int maxIdx = 0;
        for (int j = 0; j < window; ++j) {
            if (isnan(a[i - window + 1 + j])) {
                has_nan = true;
                break;
            }
            if (a[i - window + 1 + j] > a[i - window + 1 + maxIdx]) maxIdx = j;
        }
        if (!has_nan) result[i] = (float)(maxIdx + 1);
    }

    return result;
}

inline vector<float> ts_argmin(const vector<float>& a, int window = 10) {
    size_t n = a.size();
    vector<float> result(n, NAN);

    for (size_t i = window - 1; i < n; ++i) {
        bool has_nan = false;
        int minIdx = 0;
        for (int j = 0; j < window; ++j) {
            if (isnan(a[i - window + 1 + j])) {
                has_nan = true;
                break;
            }
            if (a[i - window + 1 + j] < a[i - window + 1 + minIdx]) minIdx = j;
        }
        if (!has_nan) result[i] = (float)(minIdx + 1);
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

#endif  // ALPHA101UTILS_H
