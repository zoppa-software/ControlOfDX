#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>初期化例外を表現する。</summary>
    public ref class InitializeException
        : Exception
    {
    public:
        /// <summary>デフォルトコンストラクタ。</summary>
        InitializeException()
            : Exception()
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        InitializeException(String ^ message)
            : Exception(message)
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        /// <param name="innerException">内部例外参照。</param>
        InitializeException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        virtual ~InitializeException()
        {}
    };
}

