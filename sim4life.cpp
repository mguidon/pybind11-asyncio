#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <chrono>
#include <thread>
#include <future>

namespace py = pybind11;

int doSomeStuff()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));   
    return 0;
}

std::future<int> doSomeStuffAsync()
{
    return std::async(std::launch::async, doSomeStuff);
}

PYBIND11_MODULE(sim4life, m)
{   
    py::class_<std::future<int> >(m, "FutureInt")
    .def(py::init<>())
    .def("get", &std::future<int>::get, "gets the value of the future for the task. this call is blocking, so waits until task is done");

    m.doc() = "sim4life plugin";
    m.def("doSomeStuff", &doSomeStuff, "does some stuff synchronously");
    m.def("doSomeAsyncStuff", &doSomeStuffAsync, "does some stuff ssynchronously");
}