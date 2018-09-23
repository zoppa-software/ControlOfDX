#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Globalization;

    /// <summary>�e�L�X�g�t�H�[�}�b�g�E���\�[�X�B</summary>
	public ref class VisualResourceOfTextFormat
		: public VisualResource
	{
#pragma region "fields"
	private:
        // �t�H�[�}�b�g����
        IDWriteTextFormat * format;

        // �t�H���g�t�@�~����
        String ^ fontFamilyName;

        // �t�H���g�E�F�C�g
        DWriteFontWeight fontWeight;

        // �t�H���g�X�^�C��
        DWriteFontStyle fontStyle;

        // �t�H���g�X�^�C��
        DWriteFontStretch fontStretch;

        // �t�H���g�T�C�Y
        float fontSize;

        // ���P�[����
        String ^ localNm;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>�t�H���g�t�@�~������ݒ�A�擾����B</summary>
        property String ^ FontFamilyName {
            String ^ get() { return this->fontFamilyName; }
            void set(String ^ value) { this->fontFamilyName = value; }
        }

        /// <summary>�t�H���g�E�F�C�g��ݒ�A�擾����B</summary>
        property DWriteFontWeight FontWeight {
            DWriteFontWeight get() { return this->fontWeight; }
            void set(DWriteFontWeight value) { this->fontWeight = value; }
        }

        /// <summary>�t�H���g�X�^�C����ݒ�A�擾����B</summary>
        property DWriteFontStyle FontStyle {
            DWriteFontStyle get() { return this->fontStyle; }
            void set(DWriteFontStyle value) { this->fontStyle = value; }
        }

        /// <summary>�t�H���g�X�g���b�`��ݒ�A�擾����B</summary>
        property DWriteFontStretch FontStretch {
            DWriteFontStretch get() { return this->fontStretch; }
            void set(DWriteFontStretch value) { this->fontStretch = value; }
        }

        /// <summary>�t�H���g�T�C�Y��ݒ�A�擾����B</summary>
        property float FontSize {
            float get() { return this->fontSize; }
            void set(float value) { this->fontSize = value; }
        }

        /// <summary>���P�[������ݒ�A�擾����B</summary>
        property String ^ LocalName {
            String ^ get() { return this->localNm; }
            void set(String ^ value) { this->localNm = value; }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        VisualResourceOfTextFormat(String ^ name)
			: VisualResource(name),
              format(NULL),
              fontFamilyName(String::Empty),
              fontWeight(DWriteFontWeight::DWRITE_FONT_WEIGHT_NORMAL),
              fontStretch(DWriteFontStretch::DWRITE_FONT_STRETCH_NORMAL),
              fontSize(10.5f)
        {
            this->localNm = CultureInfo::CurrentCulture->Name;
        }

        /// <summary>�f�X�g���N�^�B</summary>
        ~VisualResourceOfTextFormat()
        {
            if (this->format != NULL) {
                this->format->Release();
                this->format = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfTextFormat()
        {
            this->~VisualResourceOfTextFormat();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            IDWriteFactory * factory = SingletonFactory::GetDirectWriteFactory();
            if (factory != NULL && this->format == NULL) {
                IDWriteTextFormat * format;
                const wchar_t * familyPtr = NULL;
                if (this->fontFamilyName != nullptr) {
                    pin_ptr<const wchar_t> familyName = PtrToStringChars(this->fontFamilyName);
                    familyPtr = familyName;
                }

                pin_ptr<const wchar_t> local = (this->localNm != nullptr ?
                                                PtrToStringChars(this->localNm) : (WCHAR*)NULL);

                factory->CreateTextFormat(familyPtr,
                                          NULL,
                                          (DWRITE_FONT_WEIGHT)this->fontWeight,
                                          (DWRITE_FONT_STYLE)this->fontStyle,
                                          (DWRITE_FONT_STRETCH)this->fontStretch,
                                          this->fontSize,
                                          local,
                                          &format);
                this->format = format;
            }
        }

    internal:
        /// <summary>�R���C���^�[�t�F�C�X�̃C���X�^���X���擾����B</summary>
        IUnknown * GetWriteInstance() override
        {
            return this->format;
        }

#pragma endregion
	};
}

