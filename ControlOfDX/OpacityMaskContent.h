#pragma once

namespace ControlOfDX
{
    /// <summary>不透明マスクの内容を指定します。</summary>
    public enum class OpacityMaskContent
    {
        /// <summary>不透明度マスクにはグラフィックスが含まれています。不透明度マスクはガンマ 2.2 の色空間でブレンドされます。</summary>
        OPACITY_MASK_CONTENT_GRAPHICS = 0,
    
        /// <summary>不透明度マスクには GDI 以外のテキストが含まれています。ブレンドに使用されるガンマ空間は、レンダー ターゲットのテキスト レンダリング パラメーターから取得されます。</summary>
        OPACITY_MASK_CONTENT_TEXT_NATURAL = 1,
    
        /// <summary>不透明度マスクには、GDI 互換レンダリング モードを使用してレンダリングされるテキストが含まれています。不透明度マスクは、GDI レンダリングのガンマを使用してブレンドされます。</summary>
        OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2,

        /// <summary>無効値。</summary>
        OPACITY_MASK_CONTENT_FORCE_DWORD = -1
    };
}