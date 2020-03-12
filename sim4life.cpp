#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <chrono>
#include <thread>
#include <future>

namespace py = pybind11;

int wait(const int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));   
    return 0;
}

std::future<int> wait_async(const int seconds)
{
    return std::async(std::launch::async, wait, seconds);
}

bool IsFutureReady(std::future<int>* self)
{
    auto status = self->wait_for(std::chrono::milliseconds(10));
    return status == std::future_status::ready;

}
PYBIND11_MODULE(sim4life, m)
{   
    py::class_<std::future<int> >(m, "FutureInt")
    .def(py::init<>())
    .def("get", &std::future<int>::get, "gets the value of the future for the task. this call is blocking, so waits until task is done")
    .def("ready",&IsFutureReady);

    m.doc() = "sim4life plugin";
    m.def("wait", &wait, "does some stuff synchronously");
    m.def("wait_async", &wait_async, "does some stuff asynchronously");
}