#pragma once

#include "../ControlOfDX.h"
#include "../SingletonFactory.h"
#include "VisualResource.h"
#include "VisualResourceOfGeometry.h"
#include "VisualResourceOfPathGeometry.h"

namespace ControlOfDX
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>円形ジオメトリリソース。</summary>
    public ref class VisualResourceOfEllipseGeometry
        : public VisualResourceOfGeometry
    {
#pragma region "fields"
    private:
        // ジオメトリ
        ID2D1EllipseGeometry * geometry;

#pragma endregion

#pragma region "constructor/destructor"
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="ellipse">対象円形。</param>
        VisualResourceOfEllipseGeometry(String ^ name,
                                        Ellipse ellipse)
            : VisualResourceOfGeometry(name)
        {
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("円形ジオメトリの作成に失敗しました");
            }

            D2D1_ELLIPSE ell = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                             ellipse.RadiusX,
                                             ellipse.RadiusY);
             
            ID2D1EllipseGeometry * geo;
            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateEllipseGeometry(ell, &geo);
            if (SUCCEEDED(hr)) {
                this->geometry = geo;
            }
            else {
                throw gcnew ResourceException("円形ジオメトリの作成に失敗しました");
            }
        }

        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="centerPoint">楕円の中心。</param>
        /// <param name="radiusX">楕円のX半径。</param>
        /// <param name="radiusY">楕円のY半径。</param>
        VisualResourceOfEllipseGeometry(String ^ name,
                                        PointF centerPoint,
                                        float radiusX,
                                        float radiusY)
            : VisualResourceOfGeometry(name)
        {
            if (!SingletonFactory::GetDirect2DFactory()) {
                throw gcnew ResourceException("円形ジオメトリの作成に失敗しました");
            }

            D2D1_ELLIPSE ell = D2D1::Ellipse(D2D1::Point2F(centerPoint.X, centerPoint.Y), radiusX, radiusY);

            ID2D1EllipseGeometry * geo;
            HRESULT hr = SingletonFactory::GetDirect2DFactory()->CreateEllipseGeometry(ell, &geo);
            if (SUCCEEDED(hr)) {
                this->geometry = geo;
            }
            else {
                throw gcnew ResourceException("円形ジオメトリの作成に失敗しました");
            }
        }

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfEllipseGeometry()
        {
            if (this->geometry != NULL) {
                this->geometry->Release();
                this->geometry = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfEllipseGeometry()
        {
            this->~VisualResourceOfEllipseGeometry();
        }

#pragma endregion

#pragma region "methods"
    internal:
        /// <summary>リソースを使用する準備を行う。</summary>
        /// <param name="name">レンダーターゲット。</param>
        void Preparation(ID2D1RenderTarget * renderTarget) override
        {

        }

        /// <summary>円形ジオメトリの実体を取得する。</summary>
        /// <return>円形ジオメトリ。</return>
        ID2D1Geometry * GetGeometry() override {
            return this->geometry;
        }

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->geometry;
        }

#pragma endregion
    };
}