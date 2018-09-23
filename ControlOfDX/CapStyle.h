#pragma once

namespace ControlOfDX
{
    /// <summary>先端のスタイル。</summary>
    public enum class CapStyle
    {
        /// <summary>フラットラインスタイル。</summary>
        CAP_STYLE_FLAT = 0,

        /// <summary>四角ラインスタイル。</summary>
        CAP_STYLE_SQUARE = 1,

        /// <summary>ラウンドラインスタイル。</summary>
        CAP_STYLE_ROUND = 2,

        /// <summary>三角ラインスタイル。</summary>
        CAP_STYLE_TRIANGLE = 3,

        /// <summary>無効キャップ。</summary>
        CAP_STYLE_FORCE_DWORD = -1
    };
}

