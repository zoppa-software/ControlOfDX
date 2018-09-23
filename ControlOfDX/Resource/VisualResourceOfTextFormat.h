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

    /// <summary>テキストフォーマット・リソース。</summary>
	public ref class VisualResourceOfTextFormat
		: public VisualResource
	{
#pragma region "fields"
	private:
        // フォーマット実体
        IDWriteTextFormat * format;

        // フォントファミリ名
        String ^ fontFamilyName;

        // フォントウェイト
        DWriteFontWeight fontWeight;

        // フォントスタイル
        DWriteFontStyle fontStyle;

        // フォントスタイル
        DWriteFontStretch fontStretch;

        // フォントサイズ
        float fontSize;

        // ロケール名
        String ^ localNm;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>フォントファミリ名を設定、取得する。</summary>
        property String ^ FontFamilyName {
            String ^ get() { return this->fontFamilyName; }
            void set(String ^ value) { this->fontFamilyName = value; }
        }

        /// <summary>フォントウェイトを設定、取得する。</summary>
        property DWriteFontWeight FontWeight {
            DWriteFontWeight get() { return this->fontWeight; }
            void set(DWriteFontWeight value) { this->fontWeight = value; }
        }

        /// <summary>フォントスタイルを設定、取得する。</summary>
        property DWriteFontStyle FontStyle {
            DWriteFontStyle get() { return this->fontStyle; }
            void set(DWriteFontStyle value) { this->fontStyle = value; }
        }

        /// <summary>フォントストレッチを設定、取得する。</summary>
        property DWriteFontStretch FontStretch {
            DWriteFontStretch get() { return this->fontStretch; }
            void set(DWriteFontStretch value) { this->fontStretch = value; }
        }

        /// <summary>フォントサイズを設定、取得する。</summary>
        property float FontSize {
            float get() { return this->fontSize; }
            void set(float value) { this->fontSize = value; }
        }

        /// <summary>ロケール名を設定、取得する。</summary>
        property String ^ LocalName {
            String ^ get() { return this->localNm; }
            void set(String ^ value) { this->localNm = value; }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
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

        /// <summary>デストラクタ。</summary>
        ~VisualResourceOfTextFormat()
        {
            if (this->format != NULL) {
                this->format->Release();
                this->format = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfTextFormat()
        {
            this->~VisualResourceOfTextFormat();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
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
        /// <summary>コムインターフェイスのインスタンスを取得する。</summary>
        IUnknown * GetWriteInstance() override
        {
            return this->format;
        }

#pragma endregion
	};
}

