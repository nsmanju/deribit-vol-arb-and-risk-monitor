#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../src/top5_filter.hpp"
#include "../src/vol_engine.hpp"
namespace py = pybind11;
PYBIND11_MODULE(deribit_engine, m) {
    m.doc() = "Deribit Vol Arb C++23 Engine - Module A + B";
    py::class_<Top5Filtered>(m, "Top5Filtered")
       .def_readwrite("filtered_bid", &Top5Filtered::filtered_bid)
       .def_readwrite("filtered_ask", &Top5Filtered::filtered_ask)
       .def_readwrite("mid", &Top5Filtered::mid)
       .def_readwrite("raw_mid", &Top5Filtered::raw_mid)
       .def_readwrite("spread_bps", &Top5Filtered::spread_bps)
       .def_readwrite("edge_bps", &Top5Filtered::edge_bps)
       .def_readwrite("is_liquid", &Top5Filtered::is_liquid);
    py::class_<Top5FilterEngine>(m, "Top5FilterEngine")
       .def_static("filter_top5", &Top5FilterEngine::filter_top5)
       .def_static("benchmark_ops_per_sec", &Top5FilterEngine::benchmark_ops_per_sec);
    py::class_<VolSignal>(m, "VolSignal")
       .def_readwrite("realized_vol", &VolSignal::realized_vol)
       .def_readwrite("garch_vol", &VolSignal::garch_vol)
       .def_readwrite("iv", &VolSignal::iv)
       .def_readwrite("edge_bps", &VolSignal::edge_bps)
       .def_readwrite("long_vol", &VolSignal::long_vol)
       .def_readwrite("price", &VolSignal::price)
       .def_readwrite("is_liquid", &VolSignal::is_liquid)
       .def_readwrite("spread_bps", &VolSignal::spread_bps);
    py::class_<GARCHVolEngine>(m, "GARCHVolEngine")
       .def_static("calc_signal", &GARCHVolEngine::calc_signal)
       .def_static("calc_garch_ewma", &GARCHVolEngine::calc_garch_ewma)
       .def_static("benchmark_ops_per_sec", &GARCHVolEngine::benchmark_ops_per_sec)
       .def_static("is_vol_safe", &GARCHVolEngine::is_vol_safe);
}
