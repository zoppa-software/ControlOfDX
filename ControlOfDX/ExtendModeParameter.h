#pragma once

namespace ControlOfDX
{
    /// <summary>配置方法を指定する。</summary>
    public enum class ExtendModeParameter
    {
        /// <summary>サンプルポイントをエッジにクランプすることにより、ソースのエッジを拡張します。</summary>
        EXTEND_MODE_CLAMP = 0,

        /// <summary>ベースタイルは変換されずに描画され、残りはベースタイルを繰り返すことで塗りつぶされます。</summary>
        EXTEND_MODE_WRAP = 1,

        /// <summary>折り返しと同じですが、代替タイルが反転します。ベースタイルは変形されずに描画されます。</summary>
        EXTEND_MODE_MIRROR = 2,

        /// <summary>無効値。</summary>
        EXTEND_MODE_FORCE_DWORD = -1
    };
}
