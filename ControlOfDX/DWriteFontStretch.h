#pragma once

namespace ControlOfDX
{
    /// <summary>フォントの標準縦横比と比較して、フォントがどの程度伸縮されているかを表します。</summary>
    public enum class DWriteFontStretch
    {
        /// <summary>定義済みのフォントの伸縮: 不明 (0)。</summary>
        DWRITE_FONT_STRETCH_UNDEFINED = 0,

        /// <summary>定義済みのフォントの伸縮: Ultra-condensed (1)。</summary>
        DWRITE_FONT_STRETCH_ULTRA_CONDENSED = 1,

        /// <summary>定義済みのフォントの伸縮: Extra-condensed (2)。</summary>
        DWRITE_FONT_STRETCH_EXTRA_CONDENSED = 2,

        /// <summary>定義済みのフォントの伸縮: Condensed (3)。</summary>
        DWRITE_FONT_STRETCH_CONDENSED = 3,

        /// <summary>定義済みのフォントの伸縮: Semi-condensed (4)。</summary>
        DWRITE_FONT_STRETCH_SEMI_CONDENSED = 4,

        /// <summary>定義済みのフォントの伸縮: Normal (5)。</summary>
        DWRITE_FONT_STRETCH_NORMAL = 5,

        /// <summary>定義済みのフォントの伸縮: Medium (5)。</summary>
        DWRITE_FONT_STRETCH_MEDIUM = 5,

        /// <summary>定義済みのフォントの伸縮: Semi-expanded (6)。</summary>
        DWRITE_FONT_STRETCH_SEMI_EXPANDED = 6,

        /// <summary>定義済みのフォントの伸縮: Expanded (7)。</summary>
        DWRITE_FONT_STRETCH_EXPANDED = 7,

        /// <summary>定義済みのフォントの伸縮: Extra-expanded (8)。</summary>
        DWRITE_FONT_STRETCH_EXTRA_EXPANDED = 8,

        /// <summary>定義済みのフォントの伸縮: Ultra-expanded (9)。</summary>
        DWRITE_FONT_STRETCH_ULTRA_EXPANDED = 9
    };
}