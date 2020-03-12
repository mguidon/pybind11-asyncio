#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <chrono>
#include <thread>
#include <future>

namespace py = pybind11;

template<typename T>
T wait(const T seconds)
{
    int ms = static_cast<int>(seconds*1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));   
    return static_cast<T>(2)*seconds;
}

template <> 
std::string wait(const std::string seconds) 
{ 
    std::this_thread::sleep_for(std::chrono::milliseconds(1042));   
    return "Bazinga";
} 

template<typename T>
std::future<T> wait_async(const T seconds)
{
    return std::async(std::launch::async, wait<T>, seconds);
}

bool IsFutureReady(std::future<int>* self)
{
    auto status = self->wait_for(std::chrono::milliseconds(10));
    return status == std::future_status::ready;
}

template<typename T>
bool Ready(std::future<T>* self)
{
    auto status = self->wait_for(std::chrono::milliseconds(10));
    return status == std::future_status::ready;
}

template<typename T>
void declare_future(py::module &m, const std::string &typestr) {
    using Future = std::future<T>;
    std::string pyclass_name = std::string("Future") + typestr;
    py::class_<Future>(m, pyclass_name.c_str())
    .def(py::init<>())
    .def("get",  &Future::get)
    .def("ready", &Ready<T>);

    m.def("wait_async", &wait_async<T>, "does some stuff asynch");
    m.def("wait", &wait<T>, "does some stuff synch");
}

PYBIND11_MODULE(sim4life, m)
{   
    declare_future<float>(m, "Float");
    declare_future<double>(m, "Double");
    declare_future<int>(m, "Int");
    declare_future<std::string>(m, "String");

    m.doc() = "sim4life plugin";
}