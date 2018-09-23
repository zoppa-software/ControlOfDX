#pragma once

namespace ControlOfDX
{
    /// <summary>線種。</summary>
    public enum class DashStyle
    {
        /// <summary>ソリッド。</summary>
        DASH_STYLE_SOLID = 0,

        /// <summary>鎖線。</summary>
        DASH_STYLE_DASH = 1,

        /// <summary>点線。</summary>
        DASH_STYLE_DOT = 2,

        /// <summary>一点鎖線。</summary>
        DASH_STYLE_DASH_DOT = 3,

        /// <summary>二点鎖線。</summary>
        DASH_STYLE_DASH_DOT_DOT = 4,

        /// <summary>カスタム線種。</summary>
        DASH_STYLE_CUSTOM = 5,

        /// <summary>無効値。</summary>
        DASH_STYLE_FORCE_DWORD = -1
    };
}

