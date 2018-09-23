#pragma once

namespace ControlOfDX
{
    /// <summary>レイヤーを作成オプション。</summary>
    public enum class LayerOptions
    {
        /// <summary>このレイヤーのテキストでは、ClearType アンチエイリアシングを使用しません。</summary>
        D2D1_LAYER_OPTIONS_NONE = 0,

        /// <summary>レイヤーは ClearType テキスト用に正しくレンダリングされます。</summary>
        D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 1,

        /// <summary>無効値。。</summary>
        D2D1_LAYER_OPTIONS_FORCE_DWORD = -1
    };
}