#pragma once

namespace ControlOfDX
{
    /// <summary>図が開いているか閉じているかを示します。</summary>
    public enum class FigureEnd
    {
        /// <summary>図は開いています。</summary>
        FIGURE_END_OPEN = 0,

        /// <summary>図は閉じています。</summary>
		FIGURE_END_CLOSED = 1,

        /// <summary>無効値。</summary>
		FIGURE_END_FORCE_DWORD = -1
    };
}