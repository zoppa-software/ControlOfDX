#pragma once

namespace ControlOfDX
{
    /// <summary>2�̃W�I���g����g�ݍ��킹�邳�܂��܂ȕ��@���w�肵�܂��B</summary>
    public enum class CombineMode
    {
        /// <summary>2�̗̈�́A�����̗̈���������Č�������܂��B</summary>
        COMBINE_MODE_UNION = 0,

        /// <summary>2�̗̈�́A�����̌�_����邱�Ƃɂ���Č��������B</summary>
        COMBINE_MODE_INTERSECT = 1,

        /// <summary>2�̗̈�́A��1�̗̈�ɑ��݂��邪��2�̗̈�ɂ͑��݂��Ȃ��̈�ƁA��2�̗̈�ɑ��݂��邪��1�̗̈�ɂ͑��݂��Ȃ��̈�Ƃ����킹�Č��������B</summary>
        COMBINE_MODE_XOR = 2,

        /// <summary>��2�̗̈�͑�1�̗̈悩�珜�O�����B</summary>
        COMBINE_MODE_EXCLUDE = 3,

        /// <summary>�����l�B</summary>
        COMBINE_MODE_FORCE_DWORD = -1
    };
}