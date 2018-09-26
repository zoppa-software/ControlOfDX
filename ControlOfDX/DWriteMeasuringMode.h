#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>テキスト レイアウトに使用される測定方法を示します。</summary>
    public enum class DWriteMeasuringMode
    {
        /// <summary>グリフに最適なメトリックを使用してテキストを測定することを指定します。メトリックの値は、現在の表示解像度には依存しません。</summary>
        DWRITE_MEASURING_MODE_NATURAL = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_NATURAL,

        /// <summary>グリフ表示と互換性があるメトリックを使用してテキストを測定することを指定します。メトリックの値は、現在の表示解像度に合わせて調整されます。</summary>
        DWRITE_MEASURING_MODE_GDI_CLASSIC = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_GDI_CLASSIC,

        /// <summary>CLEARTYPE_NATURAL_QUALITY で作成されたフォントを使用して GDI によって測定されるテキストと同じグリフ表示メトリックを使用して、テキストを測定することを指定します。</summary>
        DWRITE_MEASURING_MODE_GDI_NATURAL = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_GDI_NATURAL,
    };
}