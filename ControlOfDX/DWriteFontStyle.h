#pragma once

namespace ControlOfDX
{
    /// <summary>フォント フェイスのスタイルを標準、イタリック体、または斜体として表します。</summary>
    public enum class DWriteFontStyle
    {
        /// <summary>フォント スタイル: 標準。</summary>
        DWRITE_FONT_STYLE_NORMAL,

        /// <summary>フォント スタイル: 斜体。</summary>
        DWRITE_FONT_STYLE_OBLIQUE,

        /// <summary>フォント スタイル: イタリック体。</summary>
        DWRITE_FONT_STYLE_ITALIC
    };
}