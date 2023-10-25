#include <iostream>
#include <functional>
#include <type_traits>
#include <future>
#include <memory>

namespace func
{
    template <typename ReturnType = void>
    class Callback
    {
    public:
        template <typename Func, typename... Args>
        auto register_func(Func function, Args... args)
        {
            auto task_pkg = std::make_shared<std::packaged_task<std::invoke_result_t<Func, Args...>()>>(
                std::bind(function, args...));

            if (task_pkg == nullptr)
            {
                return -1;
            }
            this->f = std::async(std::launch::deferred, [task_pkg]() -> ReturnType
                                 {                      
                           (*task_pkg)();
                           return (*task_pkg).get_future().get(); });
            return 0;
        }
        ReturnType call()
        {
            return f.get();
        }

    private:
        std::future<ReturnType> f;
    };
};