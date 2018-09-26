#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>レイアウト ボックスからオーバーフローするテキストのトリミングに使用するテキストの粒度を指定します。</summary>
    public enum class DWriteTrimmingGranularity
    {
        /// <summary>トリミングは行われません。テキストフローは、レイアウト幅を超えてレンダリングされます。</summary>
        DWRITE_TRIMMING_GRANULARITY_NONE = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_NONE,

        /// <summary>トリミングは文字クラスター境界で行われます。</summary>
        DWRITE_TRIMMING_GRANULARITY_CHARACTER = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER,

        /// <summary>トリミングは単語の境界で行われます。</summary>
        DWRITE_TRIMMING_GRANULARITY_WORD = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_WORD
    };
}