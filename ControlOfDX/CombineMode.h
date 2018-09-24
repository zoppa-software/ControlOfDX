#pragma once

namespace ControlOfDX
{
    /// <summary>2つのジオメトリを組み合わせるさまざまな方法を指定します。</summary>
    public enum class CombineMode
    {
        /// <summary>2つの領域は、両方の領域を結合して結合されます。</summary>
        COMBINE_MODE_UNION = 0,

        /// <summary>2つの領域は、それらの交点を取ることによって結合される。</summary>
        COMBINE_MODE_INTERSECT = 1,

        /// <summary>2つの領域は、第1の領域に存在するが第2の領域には存在しない領域と、第2の領域に存在するが第1の領域には存在しない領域とを合わせて結合される。</summary>
        COMBINE_MODE_XOR = 2,

        /// <summary>第2の領域は第1の領域から除外される。</summary>
        COMBINE_MODE_EXCLUDE = 3,

        /// <summary>無効値。</summary>
        COMBINE_MODE_FORCE_DWORD = -1
    };
}