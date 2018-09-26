#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>���C�A�E�g�̍s�Ԋu�Ɏg�p�������@�B</summary>
    public enum class DWriteLineSpacingMethod
    {
        /// <summary>�s�Ԋu�̓R���e���c�݂̂Ɉˑ����A�t�H���g�ƃC�����C���I�u�W�F�N�g�̃T�C�Y�ɍ��킹�đ������܂��B</summary>
        DWRITE_LINE_SPACING_METHOD_DEFAULT = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_DEFAULT,

        /// <summary>
        /// �܂܂�Ă���t�H���g�T�C�Y�ɂ�����炸�A���͖����I�Ɉ�l�ȊԊu�ɐݒ肳��܂��B
        /// ����́A�t�H���g�̃t�H�[���o�b�N���甭������s�ψ�ȊO�ς�����邽�߂ɖ𗧂��܂��B
        /// </summary>
        DWRITE_LINE_SPACING_METHOD_UNIFORM = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_UNIFORM,

        /// <summary>���C���̊Ԋu�ƃx�[�X���C���̋����́A�R���e���c�A�t�H���g�ƃC�����C���I�u�W�F�N�g�̃T�C�Y�Ɋ�Â��Čv�Z���ꂽ�l�ɔ�Ⴕ�܂��B</summary>
        DWRITE_LINE_SPACING_METHOD_PROPORTIONAL = DWRITE_LINE_SPACING_METHOD::DWRITE_LINE_SPACING_METHOD_PROPORTIONAL,
    };
}