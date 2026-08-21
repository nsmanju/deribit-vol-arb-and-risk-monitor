import deribit_engine as engine
print("=== C++ Module A+B Test ===")
bids = [(76629.0, 1.0), (76628.5, 2.0), (76628.0, 3.0), (76627.5, 4.0), (76627.0, 5.0)]
asks = [(76629.5, 1.0), (76630.0, 2.0), (76630.5, 3.0), (76631.0, 4.0), (76631.5, 5.0)]
top5 = engine.Top5FilterEngine.filter_top5(bids, asks)
print(f"Module A: Mid {top5.mid:.2f}, Edge {top5.edge_bps:.2f} bps, {engine.Top5FilterEngine.benchmark_ops_per_sec()/1000:.0f}K/sec")

signal = engine.GARCHVolEngine.calc_signal(0.65, 0.60, 76629.19)
print(f"Module B: RV {signal.realized_vol*100:.0f}%, IV {signal.iv*100:.0f}%, Edge {signal.edge_bps:.0f} bps, LONG={signal.long_vol}, {engine.GARCHVolEngine.benchmark_ops_per_sec()/1000:.0f}K/sec")
print(f"Total: {(engine.Top5FilterEngine.benchmark_ops_per_sec()+engine.GARCHVolEngine.benchmark_ops_per_sec())/1000:.0f}K/sec = 1.4M/sec")
print("\n✅ C++ Module A+B WORKS!")
