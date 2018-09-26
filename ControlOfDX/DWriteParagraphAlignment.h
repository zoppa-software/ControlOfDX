#pragma once

namespace ControlOfDX
{
    /// <summary>レイアウトボックスのフローの開始エッジと終了エッジを基準にフロー方向軸に沿った段落テキストの整列。</summary>
    public enum class DWriteParagraphAlignment
    {
        /// <summary>段落の最初の行は、レイアウトボックスのフローの開始端に揃えられます。</summary>
        DWRITE_PARAGRAPH_ALIGNMENT_NEAR,

        /// <summary>段落の最後の行は、レイアウトボックスのフローの終了辺に揃えられます。</summary>
        DWRITE_PARAGRAPH_ALIGNMENT_FAR,

        /// <summary>パラグラフの中心は、レイアウトボックスのフローの中央に揃えられます。</summary>
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER
    };
}