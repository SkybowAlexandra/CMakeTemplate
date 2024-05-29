/********************************************************************************
 * @�ļ���:
 * @����: ��
 * @�汾: 1.0
 * @ʱ��: 2022-
 * @��ʽ:
 * @˵��: ����ģʽ
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