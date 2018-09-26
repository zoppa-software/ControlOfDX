#pragma once

#include<dwrite.h>

namespace ControlOfDX
{
    /// <summary>�e�L�X�g ���C�A�E�g�Ɏg�p����鑪����@�������܂��B</summary>
    public enum class DWriteMeasuringMode
    {
        /// <summary>�O���t�ɍœK�ȃ��g���b�N���g�p���ăe�L�X�g�𑪒肷�邱�Ƃ��w�肵�܂��B���g���b�N�̒l�́A���݂̕\���𑜓x�ɂ͈ˑ����܂���B</summary>
        DWRITE_MEASURING_MODE_NATURAL = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_NATURAL,

        /// <summary>�O���t�\���ƌ݊��������郁�g���b�N���g�p���ăe�L�X�g�𑪒肷�邱�Ƃ��w�肵�܂��B���g���b�N�̒l�́A���݂̕\���𑜓x�ɍ��킹�Ē�������܂��B</summary>
        DWRITE_MEASURING_MODE_GDI_CLASSIC = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_GDI_CLASSIC,

        /// <summary>CLEARTYPE_NATURAL_QUALITY �ō쐬���ꂽ�t�H���g���g�p���� GDI �ɂ���đ��肳���e�L�X�g�Ɠ����O���t�\�����g���b�N���g�p���āA�e�L�X�g�𑪒肷�邱�Ƃ��w�肵�܂��B</summary>
        DWRITE_MEASURING_MODE_GDI_NATURAL = DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_GDI_NATURAL,
    };
}