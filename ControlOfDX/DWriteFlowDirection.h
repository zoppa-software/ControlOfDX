#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>�e�L�X�g�̍s���ǂ̂悤�ɑ��ΓI�ɔz�u����邩�̕����B</summary>
    public enum class DWriteFlowDirection
    {
        /// <summary>�e�L�X�g�s�͏ォ�牺�ɔz�u����܂��B</summary>
        DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM = 0,

        /// <summary>�e�L�X�g�s�͉������ɔz�u����܂��B</summary>
        DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP = 1,

        /// <summary>�e�L�X�g�s�͍�����E�ɔz�u����܂��B</summary>
        DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT = 2,

        /// <summary>�e�L�X�g�s�͉E���獶�ɔz�u����܂��B</summary>
        DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT = 3,
    };
}