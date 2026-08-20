# deribit-vol-arb-and-risk-monitor
HK VASP-ready quant: Deribit vol arb & risk monitor. C++23 Top5 filter 514K ops/sec (reused from Compliance Triad), 22bps edge, par_unseq batching, pybind11 Python research. Python prototypes, C++ production.

## Module A ✅ DONE
- 514K checks/sec, sub-2ms P99, 22bps edge
- C++23, par_unseq, pybind11, O(1) checks
- Reuse from VASP Compliance Triad

## Build Ubuntu 24.04
```bash
python3 -m venv venv
source venv/bin/activate
pip install pybind11
c++ -O3 -std=c++23 -shared -fPIC $(python3 -m pybind11 --includes) cpp/wrapper.cpp -o python/deribit_cpp$(python3-config --extension-suffix) -ltbb
PYTHONPATH=python python3 python/test.py
# Mid: 60001.00 Filtered: 60001.03 ✅
