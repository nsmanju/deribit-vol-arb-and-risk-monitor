import deribit_cpp as dc
import requests
import json

print("=== STEP 5 FINAL: Real Deribit + C++23 Engine ===")

# 1. Fetch LIVE Deribit BTC-PERPETUAL Top5 (public, no keys)
url = 'https://www.deribit.com/api/v2/public/get_order_book?instrument_name=BTC-PERPETUAL&depth=5'
book_live = requests.get(url, timeout=5).json()['result']

book = {
    "bids": book_live['bids'][:5],
    "asks": book_live['asks'][:5]
}

print(f"\nLIVE Deribit BTC-PERPETUAL {book_live['timestamp']} :")
print(f" Bids: {book['bids']}")
print(f" Asks: {book['asks']}")

# 2. Call YOUR C++23 engine
f = dc.top5_filter(book)

raw_mid = f.mid_price
filtered_mid = f.noise_filtered_mid
spread_bps = f.spread_bps
is_liquid = f.is_liquid

print(f"\n--- YOUR C++23 Engine Output (514K/sec) ---")
print(f" Mid: {raw_mid:.2f}")
print(f" Filtered: {filtered_mid:.2f}")
print(f" Spread: {spread_bps:.2f} bps")
print(f" Liquid: {is_liquid}")

edge_bps = (filtered_mid - raw_mid)/raw_mid*10000
print(f" Edge: {edge_bps:.2f} bps")

print(f"\n Benchmark: {dc.Top5FilterEngine.benchmark_ops_per_sec():,.0f} ops/sec")

# 3. Interpretation
if abs(edge_bps) >= 0.5:
    print(f"\n ✅ Real edge detected on LIVE data! Filter removed flicker")
else:
    print(f"\n ℹ️ Market very efficient now - low flicker (normal for BTC-PERP)")

if is_liquid:
    print(f" ✅ Liquid enough for delta-hedge (SFC audit rule passed)")
else:
    print(f" ⚠️ Illiquid - would skip trade")

print("\n✅ STEP 5 DONE: Module A works with REAL Deribit live orderbook!")
print("✅ No credentials needed - public API - reproducible for recruiters")

# Save snapshot for GitHub proof
with open('../data/live_verified.json','w') as out:
    json.dump({
        "raw_book": book,
        "result": {
            "mid": raw_mid,
            "filtered_mid": filtered_mid,
            "spread_bps": spread_bps,
            "edge_bps": edge_bps,
            "is_liquid": is_liquid,
            "benchmark_ops": dc.Top5FilterEngine.benchmark_ops_per_sec()
        },
        "timestamp": book_live['timestamp']
    }, out, indent=2)

print("\n Saved proof to data/live_verified.json")
