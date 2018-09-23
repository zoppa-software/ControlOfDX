#pragma once

namespace ControlOfDX
{
    /// <summary>非テキストプリミティブのエッジをレンダリングする方法を記述します。</summary>
    public enum class AntialiasMode
    {
        /// <summary>各プリミティブのエッジは、順次アンチエイリアシングされます。</summary>
        ANTIALIAS_MODE_PER_PRIMITIVE = 0,

        /// <summary>ピクセル中心がジオメトリに含まれる場合、各ピクセルがレンダリングされます。</summary>
        ANTIALIAS_MODE_ALIASED = 1,

        /// <summary>無効値。</summary>
        ANTIALIAS_MODE_FORCE_DWORD = -1
    };
}