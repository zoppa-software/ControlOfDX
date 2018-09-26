#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Globalization;

    /// <summary>�e�L�X�g�t�H�[�}�b�g�E���\�[�X�B</summary>
    public ref class VisualResourceOfInlineObject
        : public VisualResource
    {
#pragma region "fields"
    private:
        // �t�H�[�}�b�g����
        IDWriteInlineObject * format;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        VisualResourceOfInlineObject(String ^ name)
            : VisualResource(name)
        {
        }

        /// <summary>�f�X�g���N�^�B</summary>
        ~VisualResourceOfInlineObject()
        {
            if (this->format != NULL) {
                this->format->Release();
                this->format = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfInlineObject()
        {
            this->~VisualResourceOfInlineObject();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>���\�[�X���g�p���鏀�����s���B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            /*
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
            */
            IDWriteFactory * factory = SingletonFactory::GetDirectWriteFactory();
            if (factory != NULL && this->format == NULL) {
                factory->CreateEllipsisTrimmingSign;
            }
        }

    internal:
        /// <summary>�R���C���^�[�t�F�C�X�̃C���X�^���X���擾����B</summary>
        IUnknown * GetWriteInstance() override
        {
            return this->format;
        }

        IDWriteInlineObject * GetInlineObject()
        {
            this->format;
        }

#pragma endregion
    };
}
