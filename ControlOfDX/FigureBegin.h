#pragma once

namespace ControlOfDX
{
    /// <summary>図を塗りつぶすか塗りつぶしなしかを示します。</summary>
    public enum class FigureBegin
    {
        /// <summary>図は塗りつぶされます。</summary>
        FIGURE_BEGIN_FILLED = 0,

        /// <summary>図は塗りつぶしなしです。</summary>
        FIGURE_BEGIN_HOLLOW = 1,

        /// <summary>無効値。</summary>
        FIGURE_BEGIN_FORCE_DWORD = -1
    };
}