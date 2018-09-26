#pragma once

namespace ControlOfDX
{
    /// <summary>テキストのスナップを抑制するか、レイアウト四角形へのクリップを有効にするかを指定します。。</summary>
    public enum class DrawTextOptions
    {
        /// <summary>テキストはピクセル境界に対して垂直方向にスナップされません。この設定は、アニメーション化されているテキストに推奨されています。</summary>
        DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001,

        /// <summary>テキストはレイアウト四角形にクリップされます。</summary>
        DRAW_TEXT_OPTIONS_CLIP = 0x00000002,

        /// <summary>フォントで定義されている場合、グリフのカラーバージョンをレンダリングします。</summary>
        DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT = 0x00000004,

        /// <summary>カラーグリフビットマップのビットマップの起点はスナップされません。</summary>
        DRAW_TEXT_OPTIONS_DISABLE_COLOR_BITMAP_SNAPPING = 0x00000008,

        /// <summary>テキストはピクセル境界に対して垂直方向にスナップされますが、レイアウト四角形にはクリップされません。</summary>
        DRAW_TEXT_OPTIONS_NONE = 0x00000000,

        /// <summary>無効値。</summary>
        DRAW_TEXT_OPTIONS_FORCE_DWORD = -1,
    };
}