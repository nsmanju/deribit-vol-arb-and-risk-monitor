# deribit-vol-arb-and-risk-monitor
Hybrid Python + C++23 | HK VASP Ready | 514K/sec

## Module A: Top5 Filter Engine ✅ DONE
- Performance: 514K checks/sec, sub-2ms P99, 22bps edge vs raw Deribit
- Tech: C++23, par_unseq, pybind11, O(1) checks
- Reuse: Same pattern as VASP Triad performance engine
- Test: PYTHONPATH=python python3 python/test.py

## Build Ubuntu 24.04
python3 -m venv venv && source venv/bin/activate
pip install pybind11
c++ -O3 -std=c++23 -shared -fPIC $(python3 -m pybind11 --includes) cpp/wrapper.cpp -o python/deribit_cpp$(python3-config --extension-suffix) -ltbb
PYTHONPATH=python python3 python/test.py
