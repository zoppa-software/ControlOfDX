#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>リソース例外を表現する。</summary>
    public ref class ResourceException
        : Exception
    {
    public:
        /// <summary>デフォルトコンストラクタ。</summary>
        ResourceException()
            : Exception()
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        ResourceException(String ^ message)
            : Exception(message)
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        /// <param name="innerException">内部例外参照。</param>
        ResourceException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        virtual ~ResourceException()
        {}
    };
}
