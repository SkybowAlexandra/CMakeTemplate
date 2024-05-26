/********************************************************************************
 * @�ļ���:
 * @����: ��
 * @�汾: 1.0
 * @ʱ��: 2022-
 * @��ʽ:
 * @˵��: ����ģʽ
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