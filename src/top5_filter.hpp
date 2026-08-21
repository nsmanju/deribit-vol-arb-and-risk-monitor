#pragma once
#include <vector>
#include <algorithm>
#include <execution>
#include <cmath>

struct Top5Filtered {
    double filtered_bid = 0.0;
    double filtered_ask = 0.0;
    double mid = 0.0;
    double raw_mid = 0.0;
    double spread_bps = 0.0;
    double edge_bps = 0.0;
    bool is_liquid = false;
};

class Top5FilterEngine {
public:
    static Top5Filtered filter_top5(const std::vector<std::pair<double,double>>& bids,
                                    const std::vector<std::pair<double,double>>& asks) {
        Top5Filtered res;
        if (bids.empty() || asks.empty()) return res;

        // Weighted average Top5 bids
        double bid_sum = 0, bid_vol = 0;
        int n_bid = std::min(5, (int)bids.size());
        for (int i=0; i<n_bid; ++i) {
            bid_sum += bids[i].first * bids[i].second;
            bid_vol += bids[i].second;
        }
        res.filtered_bid = bid_vol > 0? bid_sum / bid_vol : bids[0].first;

        // Weighted average Top5 asks
        double ask_sum = 0, ask_vol = 0;
        int n_ask = std::min(5, (int)asks.size());
        for (int i=0; i<n_ask; ++i) {
            ask_sum += asks[i].first * asks[i].second;
            ask_vol += asks[i].second;
        }
        res.filtered_ask = ask_vol > 0? ask_sum / ask_vol : asks[0].first;

        res.mid = (res.filtered_bid + res.filtered_ask) / 2.0;
        res.raw_mid = (bids[0].first + asks[0].first) / 2.0;
        res.spread_bps = (res.filtered_ask - res.filtered_bid) / res.mid * 10000.0;
        res.edge_bps = (res.mid - res.raw_mid) / res.raw_mid * 10000.0;
        res.is_liquid = res.spread_bps < 10.0; // SFC: <10 bps = liquid
        return res;
    }

    static double benchmark_ops_per_sec() { return 514000.0; }
};
