#pragma once

namespace ControlOfDX
{
    /// <summary>コーナー処理。</summary>
    public enum class LineJoin
    {
        /// <summary>通常コーナー。</summary>
        LINE_JOIN_MITER = 0,

        /// <summary>面取りコーナー。</summary>
        LINE_JOIN_BEVEL = 1,

        /// <summary>丸めコーナー。</summary>
        LINE_JOIN_ROUND = 2,

        /// <summary>結合がリミットを超えない場合は標準の角度の頂点。超えた場合は傾斜の付いた頂点。</summary>
        LINE_JOIN_MITER_OR_BEVEL = 3,

        /// <summary>無効値。</summary>
        LINE_JOIN_FORCE_DWORD = -1
    };
}