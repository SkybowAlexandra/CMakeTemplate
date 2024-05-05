#pragma once
#include <iostream>
#include <functional>
#include <type_traits>
#include <future>
#include <memory>
#include <type_traits>
namespace func
{

    template <template <typename> typename Ptr, typename Cls, typename... Arg>
    Ptr<Cls> factory(Arg &&...args)
    {
        if constexpr (std::is_same_v<Ptr<Cls>, std::shared_ptr<Cls>>)
        {
            return std::make_shared<Cls>(std::forward<Arg>(args)...);
        }
        if constexpr (std::is_same_v<Ptr<Cls>, std::unique_ptr<Cls>>)
        {
            return std::make_unique<Cls>(std::forward<Arg>(args)...);
        }
        if constexpr (std::is_same_v<Ptr<Cls>, std::weak_ptr<Cls>>)
        {
            return std::weak_ptr<Cls>(std::forward<Arg>(args)...);
        }
        return nullptr;
    }

    template <typename ReturnType = void>
    class Callback
    {
    public:
        template <typename Func, typename... Args>
        void register_func(Func function, Args... args)
        {
            auto task_pkg = std::make_shared<std::packaged_task<std::invoke_result_t<Func, Args...>()>>(
                std::bind(function, args...));
            if (task_pkg.get() == nullptr)
                throw std::runtime_error("Failed to create packaged_task");
            this->f = std::async(std::launch::deferred, [task_pkg]() -> ReturnType
                                 {
                try
                {
                    (*task_pkg)();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                return (*task_pkg).get_future().get(); });
        }
        ReturnType call()
        {
            return f.get();
        }
        ~Callback()
        {
            if (f.valid())
            {
                f.wait();
            }
        }

    private:
        std::future<ReturnType> f;
    };
};