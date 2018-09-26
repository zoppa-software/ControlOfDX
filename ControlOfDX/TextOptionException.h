#pragma once

namespace ControlOfDX
{
    using namespace System;

    /// <summary>文字列描画オプション例外。</summary>
    public ref class TextOptionException
        : Exception
    {
    public:
        /// <summary>デフォルトコンストラクタ。</summary>
        TextOptionException()
            : Exception()
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        TextOptionException(String ^ message)
            : Exception(message)
        {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="message">例外メッセージ。</param>
        /// <param name="innerException">内部例外参照。</param>
        TextOptionException(String ^ message, Exception ^ innerException)
            : Exception(message, innerException)
        {}

        /// <summary>デストラクタ。</summary>
        virtual ~TextOptionException()
        {}
    };
}