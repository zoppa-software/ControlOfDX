#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>ストロークスタイルリソース。</summary>
    public ref class VisualResourceOfStrokeStyle sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>形状の輪郭を描くストロークを記述します。</summary>
        ref class StrokeStyleProperties
        {
        private:
            // ストロークジオメトリで開いている先端形状
            CapStyle startCap;

            // ストロークジオメトリで開いている終端形状
            CapStyle endCap;

            // 各ダッシュセグメントの両端の形状
            CapStyle dashCap;

            // セグメントの結合方法を示す値
            LineJoin lineJoin;

            // 接合された角の接合の厚さの制限。この値は常に1.0f以上であるかのように扱われます
            float miterLimit;

            // ストロークにダッシュパターンがあるかどうかを指定する値
            DashStyle dashStyle;

            // ダッシュシーケンス内のオフセットを指定する値
            float dashOffset;

        public:
            /// <summary>ストロークジオメトリで開いている先端形状を設定、取得する。</summary>
            property CapStyle StartCap {
                CapStyle get() { return this->startCap; }
                void set(CapStyle value) { this->startCap = value; }
            }

            /// <summary>ストロークジオメトリで開いている終端形状を設定、取得する。</summary>
            property CapStyle EndCap {
                CapStyle get() { return this->endCap; }
                void set(CapStyle value) { this->endCap = value; }
            }

            /// <summary>各ダッシュセグメントの両端の形状を設定、取得する。</summary>
            property CapStyle DashCap {
                CapStyle get() { return this->dashCap; }
                void set(CapStyle value) { this->dashCap = value; }
            }

            /// <summary>セグメントの結合方法を示す値を設定、取得する。</summary>
            property ControlOfDX::LineJoin LineJoin {
                ControlOfDX::LineJoin get() { return this->lineJoin; }
                void set(ControlOfDX::LineJoin value) { this->lineJoin = value; }
            }

            /// <summary>接合された角の接合の厚さの制限を設定、取得する。</summary>
            property float MiterLimit {
                float get() { return this->miterLimit; }
                void set(float value) { this->miterLimit = value; }
            }

            /// <summary>ストロークにダッシュパターンがあるかどうかを指定する値を設定、取得する。</summary>
            property ControlOfDX::DashStyle DashStyle {
                ControlOfDX::DashStyle get() { return this->dashStyle; }
                void set(ControlOfDX::DashStyle value) { this->dashStyle = value; }
            }

            /// <summary>ダッシュシーケンス内のオフセットを指定する値を設定、取得する。</summary>
            property float DashOffset {
                float get() { return this->dashOffset; }
                void set(float value) { this->dashOffset = value; }
            }
        };

#pragma endregion

#pragma region "fields"
	private:
        // ストロークスタイル
        ID2D1StrokeStyle * strokeStyle;

        // ストローク形状
        StrokeStyleProperties ^ properties;

        // ダッシュパターン
        List<float>^ dashes;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>形状の輪郭を描くストロークを取得する。</summary>
        property StrokeStyleProperties ^ Properties
        {
            StrokeStyleProperties ^ get() { return this->properties; }
        }

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        VisualResourceOfStrokeStyle(String ^ name)
            : VisualResource(name), strokeStyle(NULL)
        {      
            this->properties = gcnew StrokeStyleProperties();
            this->dashes = gcnew List<float>();
        }

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfStrokeStyle()
        {
            if (this->strokeStyle != NULL) {
                this->strokeStyle->Release();
                this->strokeStyle = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfStrokeStyle()
        {
            this->~VisualResourceOfStrokeStyle();
        }

#pragma endregion

#pragma region "methods"
    public:
        /// <summary>ダッシュパターンを消去する。</summary>
        void DashesClear()
        {
            this->dashes->Clear();
        }

        /// <summary>ダッシュパターンに追加する。</summary>
        /// <param name="value">追加する値。</param>
        void DashesAdd(float value)
        {
            this->dashes->Add(value);
        }

        /// <summary>ダッシュパターンに追加する。</summary>
        /// <param name="values">追加する値リスト。</param>
        void DashesAddRange(System::Collections::Generic::IEnumerable<float>^ values)
        {
            this->dashes->AddRange(values);
        }

    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            ID2D1Factory * factory = SingletonFactory::GetDirect2DFactory();
            if (this->strokeStyle == NULL && factory != NULL) {
                D2D1_STROKE_STYLE_PROPERTIES prop = D2D1::StrokeStyleProperties(
                    (D2D1_CAP_STYLE)this->properties->StartCap,
                    (D2D1_CAP_STYLE)this->properties->EndCap,
                    (D2D1_CAP_STYLE)this->properties->DashCap,
                    (D2D1_LINE_JOIN)this->properties->LineJoin,
                    this->properties->MiterLimit,
                    (D2D1_DASH_STYLE)this->properties->DashStyle,
                    this->properties->DashOffset);

                ID2D1StrokeStyle * stroke;
                std::vector<float> dhs(this->dashes->Count);
                for each (float v in this->dashes) {
                    dhs.push_back(v);
                }
                
                HRESULT hr = factory->CreateStrokeStyle(prop, (float*)dhs.data(), (UINT32)dhs.size(), &stroke);
                if (SUCCEEDED(hr)) {
                    this->strokeStyle = stroke;
                }
                else {
                    this->strokeStyle = NULL;
                }
            }
        }

        /// <summary>ストロークスタイルの実体を取得する。</summary>
        /// <return>ストロークスタイル。</return>
        ID2D1StrokeStyle * GetStrokeStyle() {
            return this->strokeStyle;
        }

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->strokeStyle;
        }

#pragma endregion
    };
}
