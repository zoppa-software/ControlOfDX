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
#pragma region "inner class"

    public:
        /// <summary>���C�A�E�g�{�b�N�X�̃I�[�o�[�t���[����e�L�X�g�̃g���~���O�I�v�V�������w�肵�܂��B</summary>
        value class Trimming
        {
        public:
            /// <summary>�g���~���O���K�p�����e�L�X�g�ו����B</summary>
            DWriteTrimmingGranularity granularity;

            /// <summary>��؂蕶���Ƃ��Ďg�p����镶���R�[�h</summary>
            unsigned int delimiter;

            /// <summary>�f���~�^������o����������߂��܂��B</summary>
            unsigned int delimiterCount;
        };

#pragma endregion

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

    public:
        /// <summary>�i���̃e�L�X�g�̕�����ݒ肵�܂��B</summary>
        /// <param name="flowDirection">�i���̃e�L�X�g�̕����B</param>
        void SetFlowDirection(DWriteFlowDirection flowDirection)
        {
            if (this->format) {
                HRESULT hr = this->format->SetFlowDirection((DWRITE_FLOW_DIRECTION)flowDirection);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�i���̃e�L�X�g�̕����ݒ莸�s");
                }
            }
        }

        /// <summary>2�̗אڂ���^�u�X�g�b�v�Ԃ̌Œ苗����ݒ肵�܂��B</summary>
        /// <param name="incrementalTabStop">�^�u�X�g�b�v�Ԃ̌Œ苗���B</param>
        void SetIncrementalTabStop(float incrementalTabStop)
        {
            if (this->format) {
                HRESULT hr = this->format->SetIncrementalTabStop(incrementalTabStop);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�^�u�X�g�b�v�Ԃ̌Œ苗���ݒ莸�s");
                }
            }
        }

        /// <summary>�s�Ԃ�ݒ肵�܂��B</summary>
        /// <param name="lineSpacingMethod">�s�Ԃ̌�����@���w�肵�܂��B</param>
        /// <param name="lineSpacing">�s�ԁA�܂�x�[�X���C���Ԃ̋����B</param> 
        /// <param name="baseline">�s�̏㕔����x�[�X���C���܂ł̋����BlineSpacing �ɑ΂���K�؂Ȕ䗦�� 80% �ł��B</param> 
        void SetLineSpacing(DWriteLineSpacingMethod lineSpacingMethod, float lineSpacing, float baseline)
        {
            if (this->format) {
                HRESULT hr = this->format->SetLineSpacing((DWRITE_LINE_SPACING_METHOD)lineSpacingMethod, lineSpacing, baseline);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�s�Ԑݒ莸�s");
                }
            }
        }

        /// <summary>���C�A�E�g�{�b�N�X�̏�[����щ��[����Ƃ����A�i���̔z�u�I�v�V������ݒ肵�܂��B</summary>
        /// <param name="paragraphAlignment">�i���̔z�u�I�v�V�����B</param>        
        void SetParagraphAlignment(DWriteParagraphAlignment paragraphAlignment)
        {
            if (this->format) {
                HRESULT hr = this->format->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)paragraphAlignment);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�i���̔z�u�I�v�V�����ݒ莸�s");
                }
            }
        }

        /// <summary>�i���̓ǂݎ�������ݒ肵�܂��B</summary>
        /// <param name="readingDirection">�e�L�X�g�̔z�u�I�v�V�����B</param>
        void SetReadingDirection(DWriteReadingDirection readingDirection)
        {
            if (this->format) {
                HRESULT hr = this->format->SetReadingDirection((DWRITE_READING_DIRECTION)readingDirection);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�i���̓ǂݎ������ݒ莸�s");
                }
            }
        }

        /// <summary>�{�b�N�X�̏�[����щ��[����Ƃ��āA�i�����̃e�L�X�g�̔z�u��ݒ肵�܂��B</summary>
        /// <param name="textAligment">�e�L�X�g�̔z�u�I�v�V�����B</param>
        void SetTextAlignment(DWriteTextAligment textAligment)
        {
            if (this->format) {
                HRESULT hr = this->format->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)textAligment);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�i�����̃e�L�X�g�̔z�u�ݒ莸�s");
                }
            }
        }

        /*
        void SetTrimming(Trimming trimmingOptions)
        {
            if (this->format) {
                DWRITE_TRIMMING trim;
                trim.granularity = (DWRITE_TRIMMING_GRANULARITY)trimmingOptions.granularity;
                trim.delimiter = trimmingOptions.delimiter;
                trim.delimiterCount = trimmingOptions.delimiterCount;

                this->format->SetTrimming(granularity, );
            }
        }
        */

        /// <summary>�E�[�ł̐܂�Ԃ��I�v�V������ݒ肵�܂��B</summary>
        /// <param name="wordWrapping">�E�[�ł̐܂�Ԃ��I�v�V�����B</param>
        void SetWordWrapping(DWriteWordWrapping wordWrapping)
        {
            if (this->format) {
                HRESULT hr = this->format->SetWordWrapping((DWRITE_WORD_WRAPPING)wordWrapping);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("�E�[�ł̐܂�Ԃ��I�v�V�����ݒ莸�s");
                }
            }
        }

#pragma endregion
	};
}

