#pragma once

namespace ControlOfDX
{
    /// <summary>�e�L�X�g�̃X�i�b�v��}�����邩�A���C�A�E�g�l�p�`�ւ̃N���b�v��L���ɂ��邩���w�肵�܂��B�B</summary>
    public enum class DrawTextOptions
    {
        /// <summary>�e�L�X�g�̓s�N�Z�����E�ɑ΂��Đ��������ɃX�i�b�v����܂���B���̐ݒ�́A�A�j���[�V����������Ă���e�L�X�g�ɐ�������Ă��܂��B</summary>
        DRAW_TEXT_OPTIONS_NO_SNAP = 0x00000001,

        /// <summary>�e�L�X�g�̓��C�A�E�g�l�p�`�ɃN���b�v����܂��B</summary>
        DRAW_TEXT_OPTIONS_CLIP = 0x00000002,

        /// <summary>�t�H���g�Œ�`����Ă���ꍇ�A�O���t�̃J���[�o�[�W�����������_�����O���܂��B</summary>
        DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT = 0x00000004,

        /// <summary>�J���[�O���t�r�b�g�}�b�v�̃r�b�g�}�b�v�̋N�_�̓X�i�b�v����܂���B</summary>
        DRAW_TEXT_OPTIONS_DISABLE_COLOR_BITMAP_SNAPPING = 0x00000008,

        /// <summary>�e�L�X�g�̓s�N�Z�����E�ɑ΂��Đ��������ɃX�i�b�v����܂����A���C�A�E�g�l�p�`�ɂ̓N���b�v����܂���B</summary>
        DRAW_TEXT_OPTIONS_NONE = 0x00000000,

        /// <summary>�����l�B</summary>
        DRAW_TEXT_OPTIONS_FORCE_DWORD = -1,
    };
}