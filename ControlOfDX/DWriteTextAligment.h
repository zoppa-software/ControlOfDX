#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>レイアウトボックスの先端および末端を基準として、読み取り方向の軸に沿って段落テキストの配置を指定します。</summary>
    public enum class DWriteTextAligment
    {
        /// <summary>段落テキストの先端が、レイアウト ボックスの先端に合わせて配置されます。</summary>
        DWRITE_TEXT_ALIGNMENT_LEADING = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING,

        /// <summary>段落テキストの末端が、レイアウト ボックスの末端に合わせて配置されます。</summary>
        DWRITE_TEXT_ALIGNMENT_TRAILING = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING,

        /// <summary>段落テキストの中心が、レイアウト ボックスの中心に合わせて配置されます。</summary>
        DWRITE_TEXT_ALIGNMENT_CENTER = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER,

        /// <summary>テキストをリーディング側に整列させ、線を埋めるためにテキストを揃えます。</summary>
        DWRITE_TEXT_ALIGNMENT_JUSTIFIED = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_JUSTIFIED,
    };
}