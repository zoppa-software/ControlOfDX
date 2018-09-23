#pragma once

#include <vector>
#include "../ControlOfDX.h"
#include "VisualResource.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>ライングラデーションブラシインスタンス。</summary>
	public ref class VisualResourceOfLinearGradientBrush sealed
        : public VisualResource
    {
#pragma region "inner class"
    public:
        /// <summary>グラデーション境界の位置と色を格納する。</summary>
        ref class GradientStop
        {
        private:
            // 色
            Color color;

            // 位置
            float position;

        public:
            /// <summary>色設定を設定、取得する。</summary>
            property Color GradientColor {
                Color get() { return this->color; }
                void set(Color val) { this->color = val; }
            }

            /// <summary>位置設定を設定、取得する。</summary>
            property float Position {
                float get() { return this->position; }
                void set(float val) { this->position = val; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            /// <param name="edgeColor">色。</param>
            /// <param name="position">位置。</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>グラデーション勾配軸の開始点と終了点を格納。</summary>
        ref class LinearGradientBrushProperties
        {
        private:
            // グラデーション軸の開始点
            PointF  startPoint;

            // グラデーション軸の終了点
            PointF  endPoint;

        public:
            /// <summary>グラデーション軸の開始点を設定、取得する。</summary>
            property PointF StartPoint {
                PointF get() { return this->startPoint; }
                void set(PointF pos) { this->startPoint = pos; }
            }

            /// <summary>グラデーション軸の終了点を設定、取得する。</summary>
            property PointF EndPoint {
                PointF get() { return this->endPoint; }
                void set(PointF pos) { this->endPoint = pos; }
            }
        };

#pragma endregion

#pragma region "fields"
	private:
        // 描画リソース
        ID2D1Resource * instance;

        // グラデーション境界の位置と色リスト
        List<GradientStop^>^ gradientStops;

        // ガンマ色空間
        GammaParameter gamma;

        // 色の引き延ばし設定
        ExtendModeParameter extendMode;

        // グラデーションの原点のオフセット、グラデーション楕円のサイズと位置
        LinearGradientBrushProperties ^ properties;

#pragma endregion

#pragma region "properties"
    public:
        /// <summary>ガンマ色空間設定を設定、取得する。</summary>
        property GammaParameter Gamma {
            GammaParameter get() { return this->gamma; }
            void set(GammaParameter gamma) { this->gamma = gamma; }
        }

        /// <summary>色の引き延ばし設定を設定、取得する。</summary>
        property ExtendModeParameter ExtendMode {
            ExtendModeParameter get() { return this->extendMode; }
            void set(ExtendModeParameter mode) { this->extendMode = mode; }
        }

        /// <summary>グラデーション勾配軸の開始点と終了点を設定、取得する。</summary>
        property LinearGradientBrushProperties ^ Propertes {
            LinearGradientBrushProperties ^ get() { return this->properties; }
        }

#pragma endregion

#pragma region "constructor/destructor"
	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
		VisualResourceOfLinearGradientBrush(String ^ name)
			: VisualResource(name),
              gamma(GammaParameter::GAMMA_2_2),
              extendMode(ExtendModeParameter::EXTEND_MODE_CLAMP)
        {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew LinearGradientBrushProperties();
        }

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfLinearGradientBrush()
        {
            this->ReleaseInstance();
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfLinearGradientBrush()
        {
            this->~VisualResourceOfLinearGradientBrush();
        }

#pragma endregion

#pragma region "methods"
	public:
        /// <summary>グラデーション境界の位置と色を全て消去する。</summary>
        void ClearGradientStops()
        {
            this->gradientStops->Clear();
        }

        /// <summary>グラデーション境界の位置と色を追加する。</summary>
        void AddGradientStop(Color edgeColor, float position)
        {
            this->gradientStops->Add(gcnew GradientStop(edgeColor, position));
        }

    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {
            if (this->instance == NULL) {
                // グラデーション境界の位置と色をリスト化する
                std::vector<D2D1_GRADIENT_STOP> pos;
                if (this->gradientStops->Count > 0) {
                    for each (GradientStop^ stp in this->gradientStops) {
                        D2D1_GRADIENT_STOP st;
                        st.color = D2D1::ColorF(stp->GradientColor.R / 255.0f,
                                                stp->GradientColor.G / 255.0f,
                                                stp->GradientColor.B / 255.0f,
                                                stp->GradientColor.A / 255.0f);
                        st.position = stp->Position;
                        pos.push_back(st);
                    }
                }
                else {
                    D2D1_GRADIENT_STOP st;
                    st.color = D2D1::ColorF(1, 1, 1, 1);
                    st.position = 1;
                    pos.push_back(st);
                }

                // グラデーション設定を行う
                ID2D1GradientStopCollection * gradientStops = NULL;
                ID2D1LinearGradientBrush * brush = NULL;
                HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                        (UINT32)pos.size(),
                                                                        (D2D1_GAMMA)this->gamma,
                                                                        (D2D1_EXTEND_MODE)this->extendMode,
                                                                        &gradientStops);
                if (SUCCEEDED(hr)) {
                    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props = D2D1::LinearGradientBrushProperties(
                        D2D1::Point2F(this->properties->StartPoint.X, this->properties->StartPoint.Y),
                        D2D1::Point2F(this->properties->EndPoint.X, this->properties->EndPoint.Y));
                    hr = renderTarget->CreateLinearGradientBrush(props, gradientStops, &brush);
                    if (SUCCEEDED(hr)) {
                        this->instance = brush;
                    }
                    else {
                        this->instance = NULL;
                    }
                    gradientStops->Release();
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