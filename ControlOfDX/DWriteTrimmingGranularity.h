#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>���C�A�E�g �{�b�N�X����I�[�o�[�t���[����e�L�X�g�̃g���~���O�Ɏg�p����e�L�X�g�̗��x���w�肵�܂��B</summary>
    public enum class DWriteTrimmingGranularity
    {
        /// <summary>�g���~���O�͍s���܂���B�e�L�X�g�t���[�́A���C�A�E�g���𒴂��ă����_�����O����܂��B</summary>
        DWRITE_TRIMMING_GRANULARITY_NONE = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_NONE,

        /// <summary>�g���~���O�͕����N���X�^�[���E�ōs���܂��B</summary>
        DWRITE_TRIMMING_GRANULARITY_CHARACTER = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER,

        /// <summary>�g���~���O�͒P��̋��E�ōs���܂��B</summary>
        DWRITE_TRIMMING_GRANULARITY_WORD = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_WORD
    };
}