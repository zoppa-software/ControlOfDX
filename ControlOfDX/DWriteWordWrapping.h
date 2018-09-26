#pragma once

namespace ControlOfDX
{
    /// <summary>�����s�̒i���̒P��̐܂�Ԃ��B</summary>
    public enum class DWriteWordWrapping
    {
        /// <summary>�e�L�X�g�̓��C�A�E�g�{�b�N�X�̃I�[�o�[�t���[������邽�߂ɁA�s�Ԃŕ�������Ă��܂��B</summary>
        DWRITE_WORD_WRAPPING_WRAP = 0,

        /// <summary>
        /// ���C�A�E�g�{�b�N�X���I�[�o�[�t���[�����Ă��A�����s�ɕۑ�����܂��B
        /// ���̃I�v�V�����́A�I�[�o�[�t���[�e�L�X�g��\�����邽�߂ɃX�N���[������ꍇ�ɂ悭�g�p����܂��B
        /// </summary>
        DWRITE_WORD_WRAPPING_NO_WRAP = 1,

        /// <summary>
        /// �e�L�X�g�̓��C�A�E�g�{�b�N�X�̃I�[�o�[�t���[������邽�߂ɁA�s�Ԃŕ�������Ă��܂��B
        /// �P�ꂪ�ő啝���傫���ꍇ�A�ً}���b�v���������܂��B
        /// </summary>
        DWRITE_WORD_WRAPPING_EMERGENCY_BREAK = 2,

        /// <summary>���C�A�E�g�̕���1�P��ł�����������ꍇ�́A�P��S�̂����b�v���A�P����󂷂��Ƃ͂���܂���i�ً}���b�s���O�j�B</summary>
        DWRITE_WORD_WRAPPING_WHOLE_WORD = 3,

        /// <summary>�C�ӂ̗L���ȕ����N���X�^�[�����b�v���܂��B</summary>
        DWRITE_WORD_WRAPPING_CHARACTER = 4,
    };
}