#pragma once

namespace ControlOfDX
{
    /// <summary>読み取りの進行方向。</summary>
    public enum class DWriteReadingDirection
    {
        /// <summary>左から右に読む。</summary>
        DWRITE_READING_DIRECTION_LEFT_TO_RIGHT = 0,

        /// <summary>右から左に読む。</summary>
        DWRITE_READING_DIRECTION_RIGHT_TO_LEFT = 1,

        /// <summary>上から下に読む。</summary>
        DWRITE_READING_DIRECTION_TOP_TO_BOTTOM = 2,

        /// <summary>下から上に読む。</summary>
        DWRITE_READING_DIRECTION_BOTTOM_TO_TOP = 3,
    };
}