#pragma once

namespace ControlOfDX
{
    /// <summary>画像が拡大縮小または回転されるときに使用されるアルゴリズムを指定します。最低画質の画像が出力されます。</summary>
    public enum class BitmapInterpolationMode
    {
        /// <summary>最も近い一点をサンプリングし、その正確な色を使用します。</summary>
        INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR = 0,

        /// <summary>4点サンプルと線形補間を使用します。</summary>
        INTERPOLATION_MODE_DEFINITION_LINEAR = 1,

        /// <summary>補間に16サンプルの3次カーネルを使用します。</summary>
        INTERPOLATION_MODE_DEFINITION_CUBIC = 2,

        /// <summary>1つのピクセル内で4つの線形サンプルを使用して、良好なエッジアンチエイリアシングを実現します。このモードは、ピクセル数が少ない画像で少量ずつ縮小するのに適しています。</summary>
        INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR = 3,

        /// <summary>異方性フィルタリングを使用して、ビットマップの変形された形状に従ってパターンをサンプリングします。</summary>
        INTERPOLATION_MODE_DEFINITION_ANISOTROPIC = 4,

        /// <summary>変換マトリクスにダウンスケーリングが含まれている場合、可変サイズの高品質キュービックカーネルを使用して画像のプリスケールを実行します。次に、最終出力に3次補間モードを使用します。</summary>
        INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC = 5,

        /// <summary>定義句。</summary>
        INTERPOLATION_MODE_DEFINITION_FANT = 6,

        /// <summary>ミップマップリニア。</summary>
        INTERPOLATION_MODE_DEFINITION_MIPMAP_LINEAR = 7,

        /// <summary>近接近隣フィルタリング。 最も近いピクセルまたは最も近い点のサンプリングとも呼ばれます。</summary>
        BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,

        /// <summary>線形フィルタリング。</summary>
        BITMAP_INTERPOLATION_MODE_LINEAR = INTERPOLATION_MODE_DEFINITION_LINEAR,

        /// <summary>無効値。</summary>
        BITMAP_INTERPOLATION_MODE_FORCE_DWORD = -1,
    };
}