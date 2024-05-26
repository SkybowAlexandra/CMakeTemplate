/********************************************************************************
 * @文件名:
 * @作者: 赵
 * @版本: 1.0
 * @时间: 2022-
 * @格式:
 * @说明: 单例模式
 ********************************************************************************/

#pragma once

namespace func
{
    template <typename T>
    class Global
    {
    public:
        static T *Get() { return *GetPPtr(); }
        template <typename... Args>
        static void New(Args &&...args)
        {
            if (Get() != nullptr)
            {
                delete Get();
            }
            *GetPPtr() = new T(std::forward<Args>(args)...);
        }
        static void Delete()
        {
            if (Get() != nullptr)
            {
                delete Get();
                *GetPPtr() = nullptr;
            }
        }

    private:
        static T **GetPPtr()
        {
            static T *ptr{nullptr};
            return &ptr;
        }
    };
};