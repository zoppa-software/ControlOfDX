#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>ビットマップブラシリソース。</summary>
    public ref class VisualResourceOfD2BitmapBrush sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>不足部の引き延ばしプロパティ。</summary>
        ref class BitmapBrushProperties
        {
        private:
            // 引き延ばし設定
            ExtendModeParameter exX, exY;

            // 補間モード
            BitmapInterpolationMode mode;

        public:
            /// <summary>横方向引き延ばし設定を設定、取得する。</summary>
            property ExtendModeParameter ExtendModeX {
                ExtendModeParameter get() { return this->exX; }
                void set(ExtendModeParameter val) { this->exX = val; }
            }

            /// <summary>縦方向引き延ばし設定を設定、取得する。</summary>
            property ExtendModeParameter ExtendModeY {
                ExtendModeParameter get() { return this->exY; }
                void set(ExtendModeParameter val) { this->exY = val; }
            }

            /// <summary>補間モードを設定、取得する。</summary>
            property BitmapInterpolationMode InterpolationMode {
                BitmapInterpolationMode get() { return this->mode; }
                void set(BitmapInterpolationMode val) { this->mode = val; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            BitmapBrushProperties()
                : exX(ExtendModeParameter::EXTEND_MODE_WRAP),
                exY(ExtendModeParameter::EXTEND_MODE_WRAP),
                mode(BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
            {}
        };

#pragma endregion

#pragma region "fields"
    private:
        // 描画リソース
        ID2D1Resource * instance;

        // 描画ビットマップ
        VisualResourceOfBitmap ^ bitmap;

        // 配置モードプロパティ
        BitmapBrushProperties ^ properties;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>描画するビットマップを設定、取得する。</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap->Source; }
            void set(Bitmap ^ bit) {
                this->ReleaseInstance();
                this->bitmap->Source = (Bitmap^)bit->Clone();
            }
        }

        /// <summary>ビットマップを配置するための不足部の引き延ばしプロパティを取得する。</summary>
        property BitmapBrushProperties ^ Properties
        {
            BitmapBrushProperties ^ get() { return this->properties; }
        }

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">描画ビットマップ。</param>
        VisualResourceOfD2BitmapBrush(String ^ name, VisualResourceOfBitmap ^ bitmap)
            : VisualResource(name), bitmap(bitmap)
        {
            this->properties = gcnew BitmapBrushProperties();
        }

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfD2BitmapBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfD2BitmapBrush()
        {
            this->~VisualResourceOfD2BitmapBrush();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            HRESULT hr;
            ID2D1BitmapBrush * brush;

            if (this->instance == NULL) {
                // ビットマップブラシを作成する
                hr = renderTarget->CreateBitmapBrush((ID2D1Bitmap*)bitmap->GetInstance(),
                                                     D2D1::BitmapBrushProperties((D2D1_EXTEND_MODE)this->properties->ExtendModeX,
                                                                                 (D2D1_EXTEND_MODE)this->properties->ExtendModeY,
                                                                                 (D2D1_BITMAP_INTERPOLATION_MODE)this->properties->InterpolationMode),
                                                     &brush);

                // ブラシを保持する
                if (SUCCEEDED(hr)) {
                    this->instance = brush;
                }
                else {
                    this->instance = NULL;
                }
            }
        }

    internal:
        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->instance;
        }

        /// <summary>描画インスタンスを解放する。</summary>
        void ReleaseInstance() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

    public:
        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetOpacity(opacity / 255.0f);
            }
        }

        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform()
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Identity());
            }
        }

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(float offsetX, float offsetY)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Translation(offsetX, offsetY));
            }
        }

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix)
        {
            if (this->instance != NULL) {
                ((ID2D1Brush*)this->instance)->SetTransform(matrix.Convert());
            }
        }

#pragma endregion
    };
}