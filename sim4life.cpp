#include <pybind11/pybind11.h>

// #include <chrono>
// #include <thread>
// #include <future>

namespace py = pybind11;

int add(int i, int j)
{
    return i+j;
}

// py::class_<std::future<int> >(moduleSystem, "FutureInt")
//     .def(py::init<>())
//     .def("get", &std::future<int>::get, "gets the value of the future for the task. this call is blocking, so waits until task is done");


//int doSomeStuff()
//{
//    std::this_thread::sleep_for(std::chrono::seconds(3));   
//    return 0;
//}

//std::future<int> doSomeStuffAsync()
//{
//    return std::async(std::launch::async, doSomeStuff);
//}

PYBIND11_MODULE(sim4life, m)
{   
    m.doc() = "sim4life plugin";
    m.def("add", &add, "A function which adds two numbers");
    //m.def("doSomeStuff", &doSomeStuff, "does some stuff synchronously");
}