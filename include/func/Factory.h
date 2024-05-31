/********************************************************************************
* @文件名:
* @作者: 赵
* @版本: 1.0
* @时间: 2022-
* @格式: 
* @说明: 工厂模式
********************************************************************************/

#pragma once
#include <vector>
#include <memory>
#include <optional>
namespace func
{
    template <typename Class, typename... Arg>
    class Factory
    {
    public:
        Factory() = delete;
        Factory(Factory &)=delete;
        static std::unique_ptr<Class> Create(Arg &&...args)
        {
            return std::make_unique<Class>(std::forward<Arg>(args)...);
        }
    };
};