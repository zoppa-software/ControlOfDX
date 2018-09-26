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
#pragma region "inner class"

    public:
        /// <summary>レイアウトボックスのオーバーフローするテキストのトリミングオプションを指定します。</summary>
        value class Trimming
        {
        public:
            /// <summary>トリミングが適用されるテキスト細分性。</summary>
            DWriteTrimmingGranularity granularity;

            /// <summary>区切り文字として使用される文字コード</summary>
            unsigned int delimiter;

            /// <summary>デリミタが何回出現したかを戻します。</summary>
            unsigned int delimiterCount;
        };

#pragma endregion

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

    public:
        /// <summary>段落のテキストの方向を設定します。</summary>
        /// <param name="flowDirection">段落のテキストの方向。</param>
        void SetFlowDirection(DWriteFlowDirection flowDirection)
        {
            if (this->format) {
                HRESULT hr = this->format->SetFlowDirection((DWRITE_FLOW_DIRECTION)flowDirection);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("段落のテキストの方向設定失敗");
                }
            }
        }

        /// <summary>2つの隣接するタブストップ間の固定距離を設定します。</summary>
        /// <param name="incrementalTabStop">タブストップ間の固定距離。</param>
        void SetIncrementalTabStop(float incrementalTabStop)
        {
            if (this->format) {
                HRESULT hr = this->format->SetIncrementalTabStop(incrementalTabStop);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("タブストップ間の固定距離設定失敗");
                }
            }
        }

        /// <summary>行間を設定します。</summary>
        /// <param name="lineSpacingMethod">行間の決定方法を指定します。</param>
        /// <param name="lineSpacing">行間、つまりベースライン間の距離。</param> 
        /// <param name="baseline">行の上部からベースラインまでの距離。lineSpacing に対する適切な比率は 80% です。</param> 
        void SetLineSpacing(DWriteLineSpacingMethod lineSpacingMethod, float lineSpacing, float baseline)
        {
            if (this->format) {
                HRESULT hr = this->format->SetLineSpacing((DWRITE_LINE_SPACING_METHOD)lineSpacingMethod, lineSpacing, baseline);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("行間設定失敗");
                }
            }
        }

        /// <summary>レイアウトボックスの上端および下端を基準とした、段落の配置オプションを設定します。</summary>
        /// <param name="paragraphAlignment">段落の配置オプション。</param>        
        void SetParagraphAlignment(DWriteParagraphAlignment paragraphAlignment)
        {
            if (this->format) {
                HRESULT hr = this->format->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)paragraphAlignment);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("段落の配置オプション設定失敗");
                }
            }
        }

        /// <summary>段落の読み取り方向を設定します。</summary>
        /// <param name="readingDirection">テキストの配置オプション。</param>
        void SetReadingDirection(DWriteReadingDirection readingDirection)
        {
            if (this->format) {
                HRESULT hr = this->format->SetReadingDirection((DWRITE_READING_DIRECTION)readingDirection);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("段落の読み取り方向設定失敗");
                }
            }
        }

        /// <summary>ボックスの上端および下端を基準として、段落内のテキストの配置を設定します。</summary>
        /// <param name="textAligment">テキストの配置オプション。</param>
        void SetTextAlignment(DWriteTextAligment textAligment)
        {
            if (this->format) {
                HRESULT hr = this->format->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)textAligment);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("段落内のテキストの配置設定失敗");
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

        /// <summary>右端での折り返しオプションを設定します。</summary>
        /// <param name="wordWrapping">右端での折り返しオプション。</param>
        void SetWordWrapping(DWriteWordWrapping wordWrapping)
        {
            if (this->format) {
                HRESULT hr = this->format->SetWordWrapping((DWRITE_WORD_WRAPPING)wordWrapping);
                if (FAILED(hr)) {
                    throw gcnew TextOptionException("右端での折り返しオプション設定失敗");
                }
            }
        }

#pragma endregion
	};
}

