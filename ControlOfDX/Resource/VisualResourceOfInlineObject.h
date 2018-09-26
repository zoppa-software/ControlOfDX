#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Globalization;

    /// <summary>テキストフォーマット・リソース。</summary>
    public ref class VisualResourceOfInlineObject
        : public VisualResource
    {
#pragma region "fields"
    private:
        // フォーマット実体
        IDWriteInlineObject * format;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        VisualResourceOfInlineObject(String ^ name)
            : VisualResource(name)
        {
        }

        /// <summary>デストラクタ。</summary>
        ~VisualResourceOfInlineObject()
        {
            if (this->format != NULL) {
                this->format->Release();
                this->format = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfInlineObject()
        {
            this->~VisualResourceOfInlineObject();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
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
        /// <summary>コムインターフェイスのインスタンスを取得する。</summary>
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
