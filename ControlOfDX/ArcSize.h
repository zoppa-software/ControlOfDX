#pragma once

namespace ControlOfDX
{
    /// <summary>弧を 180°より大きくするかどうかを指定します。</summary>
    public enum class ArcSize
    {
        /// <summary>孤の掃引を 180°以下にします。</summary>
        ARC_SIZE_SMALL = 0,

        /// <summary>孤の掃引を 180°以上にします。</summary>
        ARC_SIZE_LARGE = 1,

        /// <summary>無効値。</summary>
        ARC_SIZE_FORCE_DWORD = -1
    };
}
