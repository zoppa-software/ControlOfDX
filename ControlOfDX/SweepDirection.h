#pragma once

namespace ControlOfDX
{
    /// <summary>楕円の弧が描画される方向を定義します。</summary>
    public enum class SweepDirection
    {
        /// <summary>弧は半時計回り (負の角度) 方向に描画されます。</summary>
        SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,

        /// <summary>弧は時計回り (正の角度) 方向に描画されます。</summary>
        SWEEP_DIRECTION_CLOCKWISE = 1,

        /// <summary>無効値。</summary>
        SWEEP_DIRECTION_FORCE_DWORD = -1
    };
}
