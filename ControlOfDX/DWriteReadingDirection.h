#pragma once

namespace ControlOfDX
{
    /// <summary>�ǂݎ��̐i�s�����B</summary>
    public enum class DWriteReadingDirection
    {
        /// <summary>������E�ɓǂށB</summary>
        DWRITE_READING_DIRECTION_LEFT_TO_RIGHT = 0,

        /// <summary>�E���獶�ɓǂށB</summary>
        DWRITE_READING_DIRECTION_RIGHT_TO_LEFT = 1,

        /// <summary>�ォ�牺�ɓǂށB</summary>
        DWRITE_READING_DIRECTION_TOP_TO_BOTTOM = 2,

        /// <summary>�������ɓǂށB</summary>
        DWRITE_READING_DIRECTION_BOTTOM_TO_TOP = 3,
    };
}