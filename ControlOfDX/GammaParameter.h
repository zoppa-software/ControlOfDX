#pragma once

namespace ControlOfDX
{
    /// <summary>ガンマ色空間設定。</summary>
    public enum class GammaParameter
    {
        /// <summary>2.2ガンマ色空間で補間される。</summary>
        GAMMA_2_2 = 0,

        /// <summary>1.0ガンマ色空間で補間される。</summary>
        GAMMA_1_0 = 1,

        /// <summary>無効値。</summary>
        GAMMA_FORCE_DWORD = -1
    };
}

