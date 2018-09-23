#pragma once

#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>単色ブラシリソース。</summary>
	public ref class VisualResourceOfSolidColorBrush sealed
		: public VisualResource
	{
#pragma region "fields"
	private:
        // 色成分値
        float alpha, red, green, blue;

        // 描画リソース
        ID2D1Resource * instance;

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="red">赤色成分値。</param>
        /// <param name="green">緑色成分値。</param>
        /// <param name="blue">青色成分値。</param>
        /// <param name="alpha">透明成分値。</param>
		VisualResourceOfSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
			: VisualResource(name),
              alpha(alpha / 255.0f),
              red(red / 255.0f),
              green(green / 255.0f),
              blue(blue / 255.0f) {}

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfSolidColorBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfSolidColorBrush()
        {
            this->~VisualResourceOfSolidColorBrush();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->instance == NULL) {
                ID2D1SolidColorBrush * brush;
                D2D1_COLOR_F color = D2D1::ColorF(this->red, this->green, this->blue, this->alpha);
                HRESULT hr = renderTarget->CreateSolidColorBrush(color, &brush);
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
        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(Color color)
        {
            this->red = red / 255.0f;
            this->green = green / 255.0f;
            this->blue = blue / 255.0f;

            if (this->instance != NULL) {
                D2D1_COLOR_F clr = D2D1::ColorF(color.R / 255.0f,
                                                color.G / 255.0f,
                                                color.B / 255.0f,
                                                color.A / 255.0f);
                ((ID2D1SolidColorBrush*)this->instance)->SetColor(clr);
            }
        }

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity)
        {
            this->alpha = opacity / 255.0f;

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
