#pragma once

namespace ControlOfDX
{
    /// <summary>複数行の段落の単語の折り返し。</summary>
    public enum class DWriteWordWrapping
    {
        /// <summary>テキストはレイアウトボックスのオーバーフローを避けるために、行間で分割されています。</summary>
        DWRITE_WORD_WRAPPING_WRAP = 0,

        /// <summary>
        /// レイアウトボックスをオーバーフローさせても、同じ行に保存されます。
        /// このオプションは、オーバーフローテキストを表示するためにスクロールする場合によく使用されます。
        /// </summary>
        DWRITE_WORD_WRAPPING_NO_WRAP = 1,

        /// <summary>
        /// テキストはレイアウトボックスのオーバーフローを避けるために、行間で分割されています。
        /// 単語が最大幅より大きい場合、緊急ラップが発生します。
        /// </summary>
        DWRITE_WORD_WRAPPING_EMERGENCY_BREAK = 2,

        /// <summary>レイアウトの幅が1単語でも小さすぎる場合は、単語全体をラップし、単語を壊すことはありません（緊急ラッピング）。</summary>
        DWRITE_WORD_WRAPPING_WHOLE_WORD = 3,

        /// <summary>任意の有効な文字クラスターをラップします。</summary>
        DWRITE_WORD_WRAPPING_CHARACTER = 4,
    };
}