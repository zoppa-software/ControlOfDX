#pragma once

namespace ControlOfDX
{
    /// <summary>ストロークの細さまたは太さという観点で、書体の濃淡を表します。</summary>
    public enum class DWriteFontWeight
    {
        /// <summary>定義済みのフォントの太さ: Thin (100)</summary>
        DWRITE_FONT_WEIGHT_THIN = 100,

        /// <summary>定義済みのフォントの太さ: Extra-light (200)</summary>
        DWRITE_FONT_WEIGHT_EXTRA_LIGHT = 200,

        /// <summary>定義済みのフォントの太さ: Ultra-light (200)</summary>
        DWRITE_FONT_WEIGHT_ULTRA_LIGHT = 200,

        /// <summary>定義済みのフォントの太さ: Light (300)</summary>
        DWRITE_FONT_WEIGHT_LIGHT = 300,

        /// <summary>定義済みのフォントの太さ: Semi Light (350)</summary>
        DWRITE_FONT_WEIGHT_SEMI_LIGHT = 350,

        /// <summary>定義済みのフォントの太さ: Normal (400)</summary>
        DWRITE_FONT_WEIGHT_NORMAL = 400,

        /// <summary>定義済みのフォントの太さ: Regular (400)</summary>
        DWRITE_FONT_WEIGHT_REGULAR = 400,

        /// <summary>定義済みのフォントの太さ: Medium (500)</summary>
        DWRITE_FONT_WEIGHT_MEDIUM = 500,

        /// <summary>定義済みのフォントの太さ: Demi-bold (600)</summary>
        DWRITE_FONT_WEIGHT_DEMI_BOLD = 600,

        /// <summary>定義済みのフォントの太さ: Semi-bold (600)</summary>
        DWRITE_FONT_WEIGHT_SEMI_BOLD = 600,

        /// <summary>定義済みのフォントの太さ: Bold (700)</summary>
        DWRITE_FONT_WEIGHT_BOLD = 700,

        /// <summary>定義済みのフォントの太さ: Extra-bold (800)</summary>
        DWRITE_FONT_WEIGHT_EXTRA_BOLD = 800,

        /// <summary>定義済みのフォントの太さ: Ultra-bold (800)</summary>
        DWRITE_FONT_WEIGHT_ULTRA_BOLD = 800,

        /// <summary>定義済みのフォントの太さ: Black (900)</summary>
        DWRITE_FONT_WEIGHT_BLACK = 900,

        /// <summary>定義済みのフォントの太さ: Heavy (900)</summary>
        DWRITE_FONT_WEIGHT_HEAVY = 900,

        /// <summary>定義済みのフォントの太さ: Extra-black (950)</summary>
        DWRITE_FONT_WEIGHT_EXTRA_BLACK = 950,

        /// <summary>定義済みのフォントの太さ: Ultra-black (950)</summary>
        DWRITE_FONT_WEIGHT_ULTRA_BLACK = 950
    };
}