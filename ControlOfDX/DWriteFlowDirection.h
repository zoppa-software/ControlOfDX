#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>テキストの行がどのように相対的に配置されるかの方向。</summary>
    public enum class DWriteFlowDirection
    {
        /// <summary>テキスト行は上から下に配置されます。</summary>
        DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM = 0,

        /// <summary>テキスト行は下から上に配置されます。</summary>
        DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP = 1,

        /// <summary>テキスト行は左から右に配置されます。</summary>
        DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT = 2,

        /// <summary>テキスト行は右から左に配置されます。</summary>
        DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT = 3,
    };
}