#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>���C�A�E�g�{�b�N�X�̐�[����і��[����Ƃ��āA�ǂݎ������̎��ɉ����Ēi���e�L�X�g�̔z�u���w�肵�܂��B</summary>
    public enum class DWriteTextAligment
    {
        /// <summary>�i���e�L�X�g�̐�[���A���C�A�E�g �{�b�N�X�̐�[�ɍ��킹�Ĕz�u����܂��B</summary>
        DWRITE_TEXT_ALIGNMENT_LEADING = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING,

        /// <summary>�i���e�L�X�g�̖��[���A���C�A�E�g �{�b�N�X�̖��[�ɍ��킹�Ĕz�u����܂��B</summary>
        DWRITE_TEXT_ALIGNMENT_TRAILING = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING,

        /// <summary>�i���e�L�X�g�̒��S���A���C�A�E�g �{�b�N�X�̒��S�ɍ��킹�Ĕz�u����܂��B</summary>
        DWRITE_TEXT_ALIGNMENT_CENTER = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER,

        /// <summary>�e�L�X�g�����[�f�B���O���ɐ��񂳂��A���𖄂߂邽�߂Ƀe�L�X�g�𑵂��܂��B</summary>
        DWRITE_TEXT_ALIGNMENT_JUSTIFIED = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_JUSTIFIED,
    };
}