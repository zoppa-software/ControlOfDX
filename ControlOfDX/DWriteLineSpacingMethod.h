#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>レイアウトの行間隔に使用される方法。</summary>
    public enum class DWriteLineSpacingMethod
    {
        /// <summary>行間隔はコンテンツのみに依存し、フォントとインラインオブジェクトのサイズに合わせて増加します。</summary>
        DWRITE_LINE_SPACING_METHOD_DEFAULT = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_DEFAULT,

        /// <summary>
        /// 含まれているフォントサイズにかかわらず、線は明示的に一様な間隔に設定されます。
        /// これは、フォントのフォールバックから発生する不均一な外観を避けるために役立ちます。
        /// </summary>
        DWRITE_LINE_SPACING_METHOD_UNIFORM = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_UNIFORM,

        /// <summary>ラインの間隔とベースラインの距離は、コンテンツ、フォントとインラインオブジェクトのサイズに基づいて計算された値に比例します。</summary>
        DWRITE_LINE_SPACING_METHOD_PROPORTIONAL = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_PROPORTIONAL,
    };
}